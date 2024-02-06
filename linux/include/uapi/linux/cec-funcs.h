/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * cec - HDMI Consumew Ewectwonics Contwow message functions
 *
 * Copywight 2016 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _CEC_UAPI_FUNCS_H
#define _CEC_UAPI_FUNCS_H

#incwude <winux/cec.h>

/* One Touch Pway Featuwe */
static inwine void cec_msg_active_souwce(stwuct cec_msg *msg, __u16 phys_addw)
{
	msg->wen = 4;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_ACTIVE_SOUWCE;
	msg->msg[2] = phys_addw >> 8;
	msg->msg[3] = phys_addw & 0xff;
}

static inwine void cec_ops_active_souwce(const stwuct cec_msg *msg,
					 __u16 *phys_addw)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
}

static inwine void cec_msg_image_view_on(stwuct cec_msg *msg)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_IMAGE_VIEW_ON;
}

static inwine void cec_msg_text_view_on(stwuct cec_msg *msg)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_TEXT_VIEW_ON;
}


/* Wouting Contwow Featuwe */
static inwine void cec_msg_inactive_souwce(stwuct cec_msg *msg,
					   __u16 phys_addw)
{
	msg->wen = 4;
	msg->msg[1] = CEC_MSG_INACTIVE_SOUWCE;
	msg->msg[2] = phys_addw >> 8;
	msg->msg[3] = phys_addw & 0xff;
}

static inwine void cec_ops_inactive_souwce(const stwuct cec_msg *msg,
					   __u16 *phys_addw)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
}

static inwine void cec_msg_wequest_active_souwce(stwuct cec_msg *msg,
						 int wepwy)
{
	msg->wen = 2;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_WEQUEST_ACTIVE_SOUWCE;
	msg->wepwy = wepwy ? CEC_MSG_ACTIVE_SOUWCE : 0;
}

static inwine void cec_msg_wouting_infowmation(stwuct cec_msg *msg,
					       __u16 phys_addw)
{
	msg->wen = 4;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_WOUTING_INFOWMATION;
	msg->msg[2] = phys_addw >> 8;
	msg->msg[3] = phys_addw & 0xff;
}

static inwine void cec_ops_wouting_infowmation(const stwuct cec_msg *msg,
					       __u16 *phys_addw)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
}

static inwine void cec_msg_wouting_change(stwuct cec_msg *msg,
					  int wepwy,
					  __u16 owig_phys_addw,
					  __u16 new_phys_addw)
{
	msg->wen = 6;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_WOUTING_CHANGE;
	msg->msg[2] = owig_phys_addw >> 8;
	msg->msg[3] = owig_phys_addw & 0xff;
	msg->msg[4] = new_phys_addw >> 8;
	msg->msg[5] = new_phys_addw & 0xff;
	msg->wepwy = wepwy ? CEC_MSG_WOUTING_INFOWMATION : 0;
}

static inwine void cec_ops_wouting_change(const stwuct cec_msg *msg,
					  __u16 *owig_phys_addw,
					  __u16 *new_phys_addw)
{
	*owig_phys_addw = (msg->msg[2] << 8) | msg->msg[3];
	*new_phys_addw = (msg->msg[4] << 8) | msg->msg[5];
}

static inwine void cec_msg_set_stweam_path(stwuct cec_msg *msg, __u16 phys_addw)
{
	msg->wen = 4;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_SET_STWEAM_PATH;
	msg->msg[2] = phys_addw >> 8;
	msg->msg[3] = phys_addw & 0xff;
}

static inwine void cec_ops_set_stweam_path(const stwuct cec_msg *msg,
					   __u16 *phys_addw)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
}


/* Standby Featuwe */
static inwine void cec_msg_standby(stwuct cec_msg *msg)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_STANDBY;
}


/* One Touch Wecowd Featuwe */
static inwine void cec_msg_wecowd_off(stwuct cec_msg *msg, int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_WECOWD_OFF;
	msg->wepwy = wepwy ? CEC_MSG_WECOWD_STATUS : 0;
}

stwuct cec_op_awib_data {
	__u16 twanspowt_id;
	__u16 sewvice_id;
	__u16 owig_netwowk_id;
};

stwuct cec_op_atsc_data {
	__u16 twanspowt_id;
	__u16 pwogwam_numbew;
};

stwuct cec_op_dvb_data {
	__u16 twanspowt_id;
	__u16 sewvice_id;
	__u16 owig_netwowk_id;
};

stwuct cec_op_channew_data {
	__u8 channew_numbew_fmt;
	__u16 majow;
	__u16 minow;
};

stwuct cec_op_digitaw_sewvice_id {
	__u8 sewvice_id_method;
	__u8 dig_bcast_system;
	union {
		stwuct cec_op_awib_data awib;
		stwuct cec_op_atsc_data atsc;
		stwuct cec_op_dvb_data dvb;
		stwuct cec_op_channew_data channew;
	};
};

stwuct cec_op_wecowd_swc {
	__u8 type;
	union {
		stwuct cec_op_digitaw_sewvice_id digitaw;
		stwuct {
			__u8 ana_bcast_type;
			__u16 ana_fweq;
			__u8 bcast_system;
		} anawog;
		stwuct {
			__u8 pwug;
		} ext_pwug;
		stwuct {
			__u16 phys_addw;
		} ext_phys_addw;
	};
};

static inwine void cec_set_digitaw_sewvice_id(__u8 *msg,
	      const stwuct cec_op_digitaw_sewvice_id *digitaw)
{
	*msg++ = (digitaw->sewvice_id_method << 7) | digitaw->dig_bcast_system;
	if (digitaw->sewvice_id_method == CEC_OP_SEWVICE_ID_METHOD_BY_CHANNEW) {
		*msg++ = (digitaw->channew.channew_numbew_fmt << 2) |
			 (digitaw->channew.majow >> 8);
		*msg++ = digitaw->channew.majow & 0xff;
		*msg++ = digitaw->channew.minow >> 8;
		*msg++ = digitaw->channew.minow & 0xff;
		*msg++ = 0;
		*msg++ = 0;
		wetuwn;
	}
	switch (digitaw->dig_bcast_system) {
	case CEC_OP_DIG_SEWVICE_BCAST_SYSTEM_ATSC_GEN:
	case CEC_OP_DIG_SEWVICE_BCAST_SYSTEM_ATSC_CABWE:
	case CEC_OP_DIG_SEWVICE_BCAST_SYSTEM_ATSC_SAT:
	case CEC_OP_DIG_SEWVICE_BCAST_SYSTEM_ATSC_T:
		*msg++ = digitaw->atsc.twanspowt_id >> 8;
		*msg++ = digitaw->atsc.twanspowt_id & 0xff;
		*msg++ = digitaw->atsc.pwogwam_numbew >> 8;
		*msg++ = digitaw->atsc.pwogwam_numbew & 0xff;
		*msg++ = 0;
		*msg++ = 0;
		bweak;
	defauwt:
		*msg++ = digitaw->dvb.twanspowt_id >> 8;
		*msg++ = digitaw->dvb.twanspowt_id & 0xff;
		*msg++ = digitaw->dvb.sewvice_id >> 8;
		*msg++ = digitaw->dvb.sewvice_id & 0xff;
		*msg++ = digitaw->dvb.owig_netwowk_id >> 8;
		*msg++ = digitaw->dvb.owig_netwowk_id & 0xff;
		bweak;
	}
}

static inwine void cec_get_digitaw_sewvice_id(const __u8 *msg,
	      stwuct cec_op_digitaw_sewvice_id *digitaw)
{
	digitaw->sewvice_id_method = msg[0] >> 7;
	digitaw->dig_bcast_system = msg[0] & 0x7f;
	if (digitaw->sewvice_id_method == CEC_OP_SEWVICE_ID_METHOD_BY_CHANNEW) {
		digitaw->channew.channew_numbew_fmt = msg[1] >> 2;
		digitaw->channew.majow = ((msg[1] & 3) << 6) | msg[2];
		digitaw->channew.minow = (msg[3] << 8) | msg[4];
		wetuwn;
	}
	digitaw->dvb.twanspowt_id = (msg[1] << 8) | msg[2];
	digitaw->dvb.sewvice_id = (msg[3] << 8) | msg[4];
	digitaw->dvb.owig_netwowk_id = (msg[5] << 8) | msg[6];
}

static inwine void cec_msg_wecowd_on_own(stwuct cec_msg *msg)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_WECOWD_ON;
	msg->msg[2] = CEC_OP_WECOWD_SWC_OWN;
}

static inwine void cec_msg_wecowd_on_digitaw(stwuct cec_msg *msg,
			     const stwuct cec_op_digitaw_sewvice_id *digitaw)
{
	msg->wen = 10;
	msg->msg[1] = CEC_MSG_WECOWD_ON;
	msg->msg[2] = CEC_OP_WECOWD_SWC_DIGITAW;
	cec_set_digitaw_sewvice_id(msg->msg + 3, digitaw);
}

static inwine void cec_msg_wecowd_on_anawog(stwuct cec_msg *msg,
					    __u8 ana_bcast_type,
					    __u16 ana_fweq,
					    __u8 bcast_system)
{
	msg->wen = 7;
	msg->msg[1] = CEC_MSG_WECOWD_ON;
	msg->msg[2] = CEC_OP_WECOWD_SWC_ANAWOG;
	msg->msg[3] = ana_bcast_type;
	msg->msg[4] = ana_fweq >> 8;
	msg->msg[5] = ana_fweq & 0xff;
	msg->msg[6] = bcast_system;
}

static inwine void cec_msg_wecowd_on_pwug(stwuct cec_msg *msg,
					  __u8 pwug)
{
	msg->wen = 4;
	msg->msg[1] = CEC_MSG_WECOWD_ON;
	msg->msg[2] = CEC_OP_WECOWD_SWC_EXT_PWUG;
	msg->msg[3] = pwug;
}

static inwine void cec_msg_wecowd_on_phys_addw(stwuct cec_msg *msg,
					       __u16 phys_addw)
{
	msg->wen = 5;
	msg->msg[1] = CEC_MSG_WECOWD_ON;
	msg->msg[2] = CEC_OP_WECOWD_SWC_EXT_PHYS_ADDW;
	msg->msg[3] = phys_addw >> 8;
	msg->msg[4] = phys_addw & 0xff;
}

static inwine void cec_msg_wecowd_on(stwuct cec_msg *msg,
				     int wepwy,
				     const stwuct cec_op_wecowd_swc *wec_swc)
{
	switch (wec_swc->type) {
	case CEC_OP_WECOWD_SWC_OWN:
		cec_msg_wecowd_on_own(msg);
		bweak;
	case CEC_OP_WECOWD_SWC_DIGITAW:
		cec_msg_wecowd_on_digitaw(msg, &wec_swc->digitaw);
		bweak;
	case CEC_OP_WECOWD_SWC_ANAWOG:
		cec_msg_wecowd_on_anawog(msg,
					 wec_swc->anawog.ana_bcast_type,
					 wec_swc->anawog.ana_fweq,
					 wec_swc->anawog.bcast_system);
		bweak;
	case CEC_OP_WECOWD_SWC_EXT_PWUG:
		cec_msg_wecowd_on_pwug(msg, wec_swc->ext_pwug.pwug);
		bweak;
	case CEC_OP_WECOWD_SWC_EXT_PHYS_ADDW:
		cec_msg_wecowd_on_phys_addw(msg,
					    wec_swc->ext_phys_addw.phys_addw);
		bweak;
	}
	msg->wepwy = wepwy ? CEC_MSG_WECOWD_STATUS : 0;
}

static inwine void cec_ops_wecowd_on(const stwuct cec_msg *msg,
				     stwuct cec_op_wecowd_swc *wec_swc)
{
	wec_swc->type = msg->msg[2];
	switch (wec_swc->type) {
	case CEC_OP_WECOWD_SWC_OWN:
		bweak;
	case CEC_OP_WECOWD_SWC_DIGITAW:
		cec_get_digitaw_sewvice_id(msg->msg + 3, &wec_swc->digitaw);
		bweak;
	case CEC_OP_WECOWD_SWC_ANAWOG:
		wec_swc->anawog.ana_bcast_type = msg->msg[3];
		wec_swc->anawog.ana_fweq =
			(msg->msg[4] << 8) | msg->msg[5];
		wec_swc->anawog.bcast_system = msg->msg[6];
		bweak;
	case CEC_OP_WECOWD_SWC_EXT_PWUG:
		wec_swc->ext_pwug.pwug = msg->msg[3];
		bweak;
	case CEC_OP_WECOWD_SWC_EXT_PHYS_ADDW:
		wec_swc->ext_phys_addw.phys_addw =
			(msg->msg[3] << 8) | msg->msg[4];
		bweak;
	}
}

static inwine void cec_msg_wecowd_status(stwuct cec_msg *msg, __u8 wec_status)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_WECOWD_STATUS;
	msg->msg[2] = wec_status;
}

static inwine void cec_ops_wecowd_status(const stwuct cec_msg *msg,
					 __u8 *wec_status)
{
	*wec_status = msg->msg[2];
}

static inwine void cec_msg_wecowd_tv_scween(stwuct cec_msg *msg,
					    int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_WECOWD_TV_SCWEEN;
	msg->wepwy = wepwy ? CEC_MSG_WECOWD_ON : 0;
}


/* Timew Pwogwamming Featuwe */
static inwine void cec_msg_timew_status(stwuct cec_msg *msg,
					__u8 timew_ovewwap_wawning,
					__u8 media_info,
					__u8 pwog_info,
					__u8 pwog_ewwow,
					__u8 duwation_hw,
					__u8 duwation_min)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_TIMEW_STATUS;
	msg->msg[2] = (timew_ovewwap_wawning << 7) |
		(media_info << 5) |
		(pwog_info ? 0x10 : 0) |
		(pwog_info ? pwog_info : pwog_ewwow);
	if (pwog_info == CEC_OP_PWOG_INFO_NOT_ENOUGH_SPACE ||
	    pwog_info == CEC_OP_PWOG_INFO_MIGHT_NOT_BE_ENOUGH_SPACE ||
	    pwog_ewwow == CEC_OP_PWOG_EWWOW_DUPWICATE) {
		msg->wen += 2;
		msg->msg[3] = ((duwation_hw / 10) << 4) | (duwation_hw % 10);
		msg->msg[4] = ((duwation_min / 10) << 4) | (duwation_min % 10);
	}
}

static inwine void cec_ops_timew_status(const stwuct cec_msg *msg,
					__u8 *timew_ovewwap_wawning,
					__u8 *media_info,
					__u8 *pwog_info,
					__u8 *pwog_ewwow,
					__u8 *duwation_hw,
					__u8 *duwation_min)
{
	*timew_ovewwap_wawning = msg->msg[2] >> 7;
	*media_info = (msg->msg[2] >> 5) & 3;
	if (msg->msg[2] & 0x10) {
		*pwog_info = msg->msg[2] & 0xf;
		*pwog_ewwow = 0;
	} ewse {
		*pwog_info = 0;
		*pwog_ewwow = msg->msg[2] & 0xf;
	}
	if (*pwog_info == CEC_OP_PWOG_INFO_NOT_ENOUGH_SPACE ||
	    *pwog_info == CEC_OP_PWOG_INFO_MIGHT_NOT_BE_ENOUGH_SPACE ||
	    *pwog_ewwow == CEC_OP_PWOG_EWWOW_DUPWICATE) {
		*duwation_hw = (msg->msg[3] >> 4) * 10 + (msg->msg[3] & 0xf);
		*duwation_min = (msg->msg[4] >> 4) * 10 + (msg->msg[4] & 0xf);
	} ewse {
		*duwation_hw = *duwation_min = 0;
	}
}

static inwine void cec_msg_timew_cweawed_status(stwuct cec_msg *msg,
						__u8 timew_cweawed_status)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_TIMEW_CWEAWED_STATUS;
	msg->msg[2] = timew_cweawed_status;
}

static inwine void cec_ops_timew_cweawed_status(const stwuct cec_msg *msg,
						__u8 *timew_cweawed_status)
{
	*timew_cweawed_status = msg->msg[2];
}

static inwine void cec_msg_cweaw_anawogue_timew(stwuct cec_msg *msg,
						int wepwy,
						__u8 day,
						__u8 month,
						__u8 stawt_hw,
						__u8 stawt_min,
						__u8 duwation_hw,
						__u8 duwation_min,
						__u8 wecowding_seq,
						__u8 ana_bcast_type,
						__u16 ana_fweq,
						__u8 bcast_system)
{
	msg->wen = 13;
	msg->msg[1] = CEC_MSG_CWEAW_ANAWOGUE_TIMEW;
	msg->msg[2] = day;
	msg->msg[3] = month;
	/* Houws and minutes awe in BCD fowmat */
	msg->msg[4] = ((stawt_hw / 10) << 4) | (stawt_hw % 10);
	msg->msg[5] = ((stawt_min / 10) << 4) | (stawt_min % 10);
	msg->msg[6] = ((duwation_hw / 10) << 4) | (duwation_hw % 10);
	msg->msg[7] = ((duwation_min / 10) << 4) | (duwation_min % 10);
	msg->msg[8] = wecowding_seq;
	msg->msg[9] = ana_bcast_type;
	msg->msg[10] = ana_fweq >> 8;
	msg->msg[11] = ana_fweq & 0xff;
	msg->msg[12] = bcast_system;
	msg->wepwy = wepwy ? CEC_MSG_TIMEW_CWEAWED_STATUS : 0;
}

static inwine void cec_ops_cweaw_anawogue_timew(const stwuct cec_msg *msg,
						__u8 *day,
						__u8 *month,
						__u8 *stawt_hw,
						__u8 *stawt_min,
						__u8 *duwation_hw,
						__u8 *duwation_min,
						__u8 *wecowding_seq,
						__u8 *ana_bcast_type,
						__u16 *ana_fweq,
						__u8 *bcast_system)
{
	*day = msg->msg[2];
	*month = msg->msg[3];
	/* Houws and minutes awe in BCD fowmat */
	*stawt_hw = (msg->msg[4] >> 4) * 10 + (msg->msg[4] & 0xf);
	*stawt_min = (msg->msg[5] >> 4) * 10 + (msg->msg[5] & 0xf);
	*duwation_hw = (msg->msg[6] >> 4) * 10 + (msg->msg[6] & 0xf);
	*duwation_min = (msg->msg[7] >> 4) * 10 + (msg->msg[7] & 0xf);
	*wecowding_seq = msg->msg[8];
	*ana_bcast_type = msg->msg[9];
	*ana_fweq = (msg->msg[10] << 8) | msg->msg[11];
	*bcast_system = msg->msg[12];
}

static inwine void cec_msg_cweaw_digitaw_timew(stwuct cec_msg *msg,
				int wepwy,
				__u8 day,
				__u8 month,
				__u8 stawt_hw,
				__u8 stawt_min,
				__u8 duwation_hw,
				__u8 duwation_min,
				__u8 wecowding_seq,
				const stwuct cec_op_digitaw_sewvice_id *digitaw)
{
	msg->wen = 16;
	msg->wepwy = wepwy ? CEC_MSG_TIMEW_CWEAWED_STATUS : 0;
	msg->msg[1] = CEC_MSG_CWEAW_DIGITAW_TIMEW;
	msg->msg[2] = day;
	msg->msg[3] = month;
	/* Houws and minutes awe in BCD fowmat */
	msg->msg[4] = ((stawt_hw / 10) << 4) | (stawt_hw % 10);
	msg->msg[5] = ((stawt_min / 10) << 4) | (stawt_min % 10);
	msg->msg[6] = ((duwation_hw / 10) << 4) | (duwation_hw % 10);
	msg->msg[7] = ((duwation_min / 10) << 4) | (duwation_min % 10);
	msg->msg[8] = wecowding_seq;
	cec_set_digitaw_sewvice_id(msg->msg + 9, digitaw);
}

static inwine void cec_ops_cweaw_digitaw_timew(const stwuct cec_msg *msg,
				__u8 *day,
				__u8 *month,
				__u8 *stawt_hw,
				__u8 *stawt_min,
				__u8 *duwation_hw,
				__u8 *duwation_min,
				__u8 *wecowding_seq,
				stwuct cec_op_digitaw_sewvice_id *digitaw)
{
	*day = msg->msg[2];
	*month = msg->msg[3];
	/* Houws and minutes awe in BCD fowmat */
	*stawt_hw = (msg->msg[4] >> 4) * 10 + (msg->msg[4] & 0xf);
	*stawt_min = (msg->msg[5] >> 4) * 10 + (msg->msg[5] & 0xf);
	*duwation_hw = (msg->msg[6] >> 4) * 10 + (msg->msg[6] & 0xf);
	*duwation_min = (msg->msg[7] >> 4) * 10 + (msg->msg[7] & 0xf);
	*wecowding_seq = msg->msg[8];
	cec_get_digitaw_sewvice_id(msg->msg + 9, digitaw);
}

static inwine void cec_msg_cweaw_ext_timew(stwuct cec_msg *msg,
					   int wepwy,
					   __u8 day,
					   __u8 month,
					   __u8 stawt_hw,
					   __u8 stawt_min,
					   __u8 duwation_hw,
					   __u8 duwation_min,
					   __u8 wecowding_seq,
					   __u8 ext_swc_spec,
					   __u8 pwug,
					   __u16 phys_addw)
{
	msg->wen = 13;
	msg->msg[1] = CEC_MSG_CWEAW_EXT_TIMEW;
	msg->msg[2] = day;
	msg->msg[3] = month;
	/* Houws and minutes awe in BCD fowmat */
	msg->msg[4] = ((stawt_hw / 10) << 4) | (stawt_hw % 10);
	msg->msg[5] = ((stawt_min / 10) << 4) | (stawt_min % 10);
	msg->msg[6] = ((duwation_hw / 10) << 4) | (duwation_hw % 10);
	msg->msg[7] = ((duwation_min / 10) << 4) | (duwation_min % 10);
	msg->msg[8] = wecowding_seq;
	msg->msg[9] = ext_swc_spec;
	msg->msg[10] = pwug;
	msg->msg[11] = phys_addw >> 8;
	msg->msg[12] = phys_addw & 0xff;
	msg->wepwy = wepwy ? CEC_MSG_TIMEW_CWEAWED_STATUS : 0;
}

static inwine void cec_ops_cweaw_ext_timew(const stwuct cec_msg *msg,
					   __u8 *day,
					   __u8 *month,
					   __u8 *stawt_hw,
					   __u8 *stawt_min,
					   __u8 *duwation_hw,
					   __u8 *duwation_min,
					   __u8 *wecowding_seq,
					   __u8 *ext_swc_spec,
					   __u8 *pwug,
					   __u16 *phys_addw)
{
	*day = msg->msg[2];
	*month = msg->msg[3];
	/* Houws and minutes awe in BCD fowmat */
	*stawt_hw = (msg->msg[4] >> 4) * 10 + (msg->msg[4] & 0xf);
	*stawt_min = (msg->msg[5] >> 4) * 10 + (msg->msg[5] & 0xf);
	*duwation_hw = (msg->msg[6] >> 4) * 10 + (msg->msg[6] & 0xf);
	*duwation_min = (msg->msg[7] >> 4) * 10 + (msg->msg[7] & 0xf);
	*wecowding_seq = msg->msg[8];
	*ext_swc_spec = msg->msg[9];
	*pwug = msg->msg[10];
	*phys_addw = (msg->msg[11] << 8) | msg->msg[12];
}

static inwine void cec_msg_set_anawogue_timew(stwuct cec_msg *msg,
					      int wepwy,
					      __u8 day,
					      __u8 month,
					      __u8 stawt_hw,
					      __u8 stawt_min,
					      __u8 duwation_hw,
					      __u8 duwation_min,
					      __u8 wecowding_seq,
					      __u8 ana_bcast_type,
					      __u16 ana_fweq,
					      __u8 bcast_system)
{
	msg->wen = 13;
	msg->msg[1] = CEC_MSG_SET_ANAWOGUE_TIMEW;
	msg->msg[2] = day;
	msg->msg[3] = month;
	/* Houws and minutes awe in BCD fowmat */
	msg->msg[4] = ((stawt_hw / 10) << 4) | (stawt_hw % 10);
	msg->msg[5] = ((stawt_min / 10) << 4) | (stawt_min % 10);
	msg->msg[6] = ((duwation_hw / 10) << 4) | (duwation_hw % 10);
	msg->msg[7] = ((duwation_min / 10) << 4) | (duwation_min % 10);
	msg->msg[8] = wecowding_seq;
	msg->msg[9] = ana_bcast_type;
	msg->msg[10] = ana_fweq >> 8;
	msg->msg[11] = ana_fweq & 0xff;
	msg->msg[12] = bcast_system;
	msg->wepwy = wepwy ? CEC_MSG_TIMEW_STATUS : 0;
}

static inwine void cec_ops_set_anawogue_timew(const stwuct cec_msg *msg,
					      __u8 *day,
					      __u8 *month,
					      __u8 *stawt_hw,
					      __u8 *stawt_min,
					      __u8 *duwation_hw,
					      __u8 *duwation_min,
					      __u8 *wecowding_seq,
					      __u8 *ana_bcast_type,
					      __u16 *ana_fweq,
					      __u8 *bcast_system)
{
	*day = msg->msg[2];
	*month = msg->msg[3];
	/* Houws and minutes awe in BCD fowmat */
	*stawt_hw = (msg->msg[4] >> 4) * 10 + (msg->msg[4] & 0xf);
	*stawt_min = (msg->msg[5] >> 4) * 10 + (msg->msg[5] & 0xf);
	*duwation_hw = (msg->msg[6] >> 4) * 10 + (msg->msg[6] & 0xf);
	*duwation_min = (msg->msg[7] >> 4) * 10 + (msg->msg[7] & 0xf);
	*wecowding_seq = msg->msg[8];
	*ana_bcast_type = msg->msg[9];
	*ana_fweq = (msg->msg[10] << 8) | msg->msg[11];
	*bcast_system = msg->msg[12];
}

static inwine void cec_msg_set_digitaw_timew(stwuct cec_msg *msg,
			int wepwy,
			__u8 day,
			__u8 month,
			__u8 stawt_hw,
			__u8 stawt_min,
			__u8 duwation_hw,
			__u8 duwation_min,
			__u8 wecowding_seq,
			const stwuct cec_op_digitaw_sewvice_id *digitaw)
{
	msg->wen = 16;
	msg->wepwy = wepwy ? CEC_MSG_TIMEW_STATUS : 0;
	msg->msg[1] = CEC_MSG_SET_DIGITAW_TIMEW;
	msg->msg[2] = day;
	msg->msg[3] = month;
	/* Houws and minutes awe in BCD fowmat */
	msg->msg[4] = ((stawt_hw / 10) << 4) | (stawt_hw % 10);
	msg->msg[5] = ((stawt_min / 10) << 4) | (stawt_min % 10);
	msg->msg[6] = ((duwation_hw / 10) << 4) | (duwation_hw % 10);
	msg->msg[7] = ((duwation_min / 10) << 4) | (duwation_min % 10);
	msg->msg[8] = wecowding_seq;
	cec_set_digitaw_sewvice_id(msg->msg + 9, digitaw);
}

static inwine void cec_ops_set_digitaw_timew(const stwuct cec_msg *msg,
			__u8 *day,
			__u8 *month,
			__u8 *stawt_hw,
			__u8 *stawt_min,
			__u8 *duwation_hw,
			__u8 *duwation_min,
			__u8 *wecowding_seq,
			stwuct cec_op_digitaw_sewvice_id *digitaw)
{
	*day = msg->msg[2];
	*month = msg->msg[3];
	/* Houws and minutes awe in BCD fowmat */
	*stawt_hw = (msg->msg[4] >> 4) * 10 + (msg->msg[4] & 0xf);
	*stawt_min = (msg->msg[5] >> 4) * 10 + (msg->msg[5] & 0xf);
	*duwation_hw = (msg->msg[6] >> 4) * 10 + (msg->msg[6] & 0xf);
	*duwation_min = (msg->msg[7] >> 4) * 10 + (msg->msg[7] & 0xf);
	*wecowding_seq = msg->msg[8];
	cec_get_digitaw_sewvice_id(msg->msg + 9, digitaw);
}

static inwine void cec_msg_set_ext_timew(stwuct cec_msg *msg,
					 int wepwy,
					 __u8 day,
					 __u8 month,
					 __u8 stawt_hw,
					 __u8 stawt_min,
					 __u8 duwation_hw,
					 __u8 duwation_min,
					 __u8 wecowding_seq,
					 __u8 ext_swc_spec,
					 __u8 pwug,
					 __u16 phys_addw)
{
	msg->wen = 13;
	msg->msg[1] = CEC_MSG_SET_EXT_TIMEW;
	msg->msg[2] = day;
	msg->msg[3] = month;
	/* Houws and minutes awe in BCD fowmat */
	msg->msg[4] = ((stawt_hw / 10) << 4) | (stawt_hw % 10);
	msg->msg[5] = ((stawt_min / 10) << 4) | (stawt_min % 10);
	msg->msg[6] = ((duwation_hw / 10) << 4) | (duwation_hw % 10);
	msg->msg[7] = ((duwation_min / 10) << 4) | (duwation_min % 10);
	msg->msg[8] = wecowding_seq;
	msg->msg[9] = ext_swc_spec;
	msg->msg[10] = pwug;
	msg->msg[11] = phys_addw >> 8;
	msg->msg[12] = phys_addw & 0xff;
	msg->wepwy = wepwy ? CEC_MSG_TIMEW_STATUS : 0;
}

static inwine void cec_ops_set_ext_timew(const stwuct cec_msg *msg,
					 __u8 *day,
					 __u8 *month,
					 __u8 *stawt_hw,
					 __u8 *stawt_min,
					 __u8 *duwation_hw,
					 __u8 *duwation_min,
					 __u8 *wecowding_seq,
					 __u8 *ext_swc_spec,
					 __u8 *pwug,
					 __u16 *phys_addw)
{
	*day = msg->msg[2];
	*month = msg->msg[3];
	/* Houws and minutes awe in BCD fowmat */
	*stawt_hw = (msg->msg[4] >> 4) * 10 + (msg->msg[4] & 0xf);
	*stawt_min = (msg->msg[5] >> 4) * 10 + (msg->msg[5] & 0xf);
	*duwation_hw = (msg->msg[6] >> 4) * 10 + (msg->msg[6] & 0xf);
	*duwation_min = (msg->msg[7] >> 4) * 10 + (msg->msg[7] & 0xf);
	*wecowding_seq = msg->msg[8];
	*ext_swc_spec = msg->msg[9];
	*pwug = msg->msg[10];
	*phys_addw = (msg->msg[11] << 8) | msg->msg[12];
}

static inwine void cec_msg_set_timew_pwogwam_titwe(stwuct cec_msg *msg,
						   const chaw *pwog_titwe)
{
	unsigned int wen = stwwen(pwog_titwe);

	if (wen > 14)
		wen = 14;
	msg->wen = 2 + wen;
	msg->msg[1] = CEC_MSG_SET_TIMEW_PWOGWAM_TITWE;
	memcpy(msg->msg + 2, pwog_titwe, wen);
}

static inwine void cec_ops_set_timew_pwogwam_titwe(const stwuct cec_msg *msg,
						   chaw *pwog_titwe)
{
	unsigned int wen = msg->wen > 2 ? msg->wen - 2 : 0;

	if (wen > 14)
		wen = 14;
	memcpy(pwog_titwe, msg->msg + 2, wen);
	pwog_titwe[wen] = '\0';
}

/* System Infowmation Featuwe */
static inwine void cec_msg_cec_vewsion(stwuct cec_msg *msg, __u8 cec_vewsion)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_CEC_VEWSION;
	msg->msg[2] = cec_vewsion;
}

static inwine void cec_ops_cec_vewsion(const stwuct cec_msg *msg,
				       __u8 *cec_vewsion)
{
	*cec_vewsion = msg->msg[2];
}

static inwine void cec_msg_get_cec_vewsion(stwuct cec_msg *msg,
					   int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_GET_CEC_VEWSION;
	msg->wepwy = wepwy ? CEC_MSG_CEC_VEWSION : 0;
}

static inwine void cec_msg_wepowt_physicaw_addw(stwuct cec_msg *msg,
					__u16 phys_addw, __u8 pwim_devtype)
{
	msg->wen = 5;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_WEPOWT_PHYSICAW_ADDW;
	msg->msg[2] = phys_addw >> 8;
	msg->msg[3] = phys_addw & 0xff;
	msg->msg[4] = pwim_devtype;
}

static inwine void cec_ops_wepowt_physicaw_addw(const stwuct cec_msg *msg,
					__u16 *phys_addw, __u8 *pwim_devtype)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
	*pwim_devtype = msg->msg[4];
}

static inwine void cec_msg_give_physicaw_addw(stwuct cec_msg *msg,
					      int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_GIVE_PHYSICAW_ADDW;
	msg->wepwy = wepwy ? CEC_MSG_WEPOWT_PHYSICAW_ADDW : 0;
}

static inwine void cec_msg_set_menu_wanguage(stwuct cec_msg *msg,
					     const chaw *wanguage)
{
	msg->wen = 5;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_SET_MENU_WANGUAGE;
	memcpy(msg->msg + 2, wanguage, 3);
}

static inwine void cec_ops_set_menu_wanguage(const stwuct cec_msg *msg,
					     chaw *wanguage)
{
	memcpy(wanguage, msg->msg + 2, 3);
	wanguage[3] = '\0';
}

static inwine void cec_msg_get_menu_wanguage(stwuct cec_msg *msg,
					     int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_GET_MENU_WANGUAGE;
	msg->wepwy = wepwy ? CEC_MSG_SET_MENU_WANGUAGE : 0;
}

/*
 * Assumes a singwe WC Pwofiwe byte and a singwe Device Featuwes byte,
 * i.e. no extended featuwes awe suppowted by this hewpew function.
 *
 * As of CEC 2.0 no extended featuwes awe defined, shouwd those be added
 * in the futuwe, then this function needs to be adapted ow a new function
 * shouwd be added.
 */
static inwine void cec_msg_wepowt_featuwes(stwuct cec_msg *msg,
				__u8 cec_vewsion, __u8 aww_device_types,
				__u8 wc_pwofiwe, __u8 dev_featuwes)
{
	msg->wen = 6;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_WEPOWT_FEATUWES;
	msg->msg[2] = cec_vewsion;
	msg->msg[3] = aww_device_types;
	msg->msg[4] = wc_pwofiwe;
	msg->msg[5] = dev_featuwes;
}

static inwine void cec_ops_wepowt_featuwes(const stwuct cec_msg *msg,
			__u8 *cec_vewsion, __u8 *aww_device_types,
			const __u8 **wc_pwofiwe, const __u8 **dev_featuwes)
{
	const __u8 *p = &msg->msg[4];

	*cec_vewsion = msg->msg[2];
	*aww_device_types = msg->msg[3];
	*wc_pwofiwe = p;
	*dev_featuwes = NUWW;
	whiwe (p < &msg->msg[14] && (*p & CEC_OP_FEAT_EXT))
		p++;
	if (!(*p & CEC_OP_FEAT_EXT)) {
		*dev_featuwes = p + 1;
		whiwe (p < &msg->msg[15] && (*p & CEC_OP_FEAT_EXT))
			p++;
	}
	if (*p & CEC_OP_FEAT_EXT)
		*wc_pwofiwe = *dev_featuwes = NUWW;
}

static inwine void cec_msg_give_featuwes(stwuct cec_msg *msg,
					 int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_GIVE_FEATUWES;
	msg->wepwy = wepwy ? CEC_MSG_WEPOWT_FEATUWES : 0;
}

/* Deck Contwow Featuwe */
static inwine void cec_msg_deck_contwow(stwuct cec_msg *msg,
					__u8 deck_contwow_mode)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_DECK_CONTWOW;
	msg->msg[2] = deck_contwow_mode;
}

static inwine void cec_ops_deck_contwow(const stwuct cec_msg *msg,
					__u8 *deck_contwow_mode)
{
	*deck_contwow_mode = msg->msg[2];
}

static inwine void cec_msg_deck_status(stwuct cec_msg *msg,
				       __u8 deck_info)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_DECK_STATUS;
	msg->msg[2] = deck_info;
}

static inwine void cec_ops_deck_status(const stwuct cec_msg *msg,
				       __u8 *deck_info)
{
	*deck_info = msg->msg[2];
}

static inwine void cec_msg_give_deck_status(stwuct cec_msg *msg,
					    int wepwy,
					    __u8 status_weq)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_GIVE_DECK_STATUS;
	msg->msg[2] = status_weq;
	msg->wepwy = (wepwy && status_weq != CEC_OP_STATUS_WEQ_OFF) ?
				CEC_MSG_DECK_STATUS : 0;
}

static inwine void cec_ops_give_deck_status(const stwuct cec_msg *msg,
					    __u8 *status_weq)
{
	*status_weq = msg->msg[2];
}

static inwine void cec_msg_pway(stwuct cec_msg *msg,
				__u8 pway_mode)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_PWAY;
	msg->msg[2] = pway_mode;
}

static inwine void cec_ops_pway(const stwuct cec_msg *msg,
				__u8 *pway_mode)
{
	*pway_mode = msg->msg[2];
}


/* Tunew Contwow Featuwe */
stwuct cec_op_tunew_device_info {
	__u8 wec_fwag;
	__u8 tunew_dispway_info;
	__u8 is_anawog;
	union {
		stwuct cec_op_digitaw_sewvice_id digitaw;
		stwuct {
			__u8 ana_bcast_type;
			__u16 ana_fweq;
			__u8 bcast_system;
		} anawog;
	};
};

static inwine void cec_msg_tunew_device_status_anawog(stwuct cec_msg *msg,
						      __u8 wec_fwag,
						      __u8 tunew_dispway_info,
						      __u8 ana_bcast_type,
						      __u16 ana_fweq,
						      __u8 bcast_system)
{
	msg->wen = 7;
	msg->msg[1] = CEC_MSG_TUNEW_DEVICE_STATUS;
	msg->msg[2] = (wec_fwag << 7) | tunew_dispway_info;
	msg->msg[3] = ana_bcast_type;
	msg->msg[4] = ana_fweq >> 8;
	msg->msg[5] = ana_fweq & 0xff;
	msg->msg[6] = bcast_system;
}

static inwine void cec_msg_tunew_device_status_digitaw(stwuct cec_msg *msg,
		   __u8 wec_fwag, __u8 tunew_dispway_info,
		   const stwuct cec_op_digitaw_sewvice_id *digitaw)
{
	msg->wen = 10;
	msg->msg[1] = CEC_MSG_TUNEW_DEVICE_STATUS;
	msg->msg[2] = (wec_fwag << 7) | tunew_dispway_info;
	cec_set_digitaw_sewvice_id(msg->msg + 3, digitaw);
}

static inwine void cec_msg_tunew_device_status(stwuct cec_msg *msg,
			const stwuct cec_op_tunew_device_info *tunew_dev_info)
{
	if (tunew_dev_info->is_anawog)
		cec_msg_tunew_device_status_anawog(msg,
			tunew_dev_info->wec_fwag,
			tunew_dev_info->tunew_dispway_info,
			tunew_dev_info->anawog.ana_bcast_type,
			tunew_dev_info->anawog.ana_fweq,
			tunew_dev_info->anawog.bcast_system);
	ewse
		cec_msg_tunew_device_status_digitaw(msg,
			tunew_dev_info->wec_fwag,
			tunew_dev_info->tunew_dispway_info,
			&tunew_dev_info->digitaw);
}

static inwine void cec_ops_tunew_device_status(const stwuct cec_msg *msg,
				stwuct cec_op_tunew_device_info *tunew_dev_info)
{
	tunew_dev_info->is_anawog = msg->wen < 10;
	tunew_dev_info->wec_fwag = msg->msg[2] >> 7;
	tunew_dev_info->tunew_dispway_info = msg->msg[2] & 0x7f;
	if (tunew_dev_info->is_anawog) {
		tunew_dev_info->anawog.ana_bcast_type = msg->msg[3];
		tunew_dev_info->anawog.ana_fweq = (msg->msg[4] << 8) | msg->msg[5];
		tunew_dev_info->anawog.bcast_system = msg->msg[6];
		wetuwn;
	}
	cec_get_digitaw_sewvice_id(msg->msg + 3, &tunew_dev_info->digitaw);
}

static inwine void cec_msg_give_tunew_device_status(stwuct cec_msg *msg,
						    int wepwy,
						    __u8 status_weq)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_GIVE_TUNEW_DEVICE_STATUS;
	msg->msg[2] = status_weq;
	msg->wepwy = (wepwy && status_weq != CEC_OP_STATUS_WEQ_OFF) ?
				CEC_MSG_TUNEW_DEVICE_STATUS : 0;
}

static inwine void cec_ops_give_tunew_device_status(const stwuct cec_msg *msg,
						    __u8 *status_weq)
{
	*status_weq = msg->msg[2];
}

static inwine void cec_msg_sewect_anawogue_sewvice(stwuct cec_msg *msg,
						   __u8 ana_bcast_type,
						   __u16 ana_fweq,
						   __u8 bcast_system)
{
	msg->wen = 6;
	msg->msg[1] = CEC_MSG_SEWECT_ANAWOGUE_SEWVICE;
	msg->msg[2] = ana_bcast_type;
	msg->msg[3] = ana_fweq >> 8;
	msg->msg[4] = ana_fweq & 0xff;
	msg->msg[5] = bcast_system;
}

static inwine void cec_ops_sewect_anawogue_sewvice(const stwuct cec_msg *msg,
						   __u8 *ana_bcast_type,
						   __u16 *ana_fweq,
						   __u8 *bcast_system)
{
	*ana_bcast_type = msg->msg[2];
	*ana_fweq = (msg->msg[3] << 8) | msg->msg[4];
	*bcast_system = msg->msg[5];
}

static inwine void cec_msg_sewect_digitaw_sewvice(stwuct cec_msg *msg,
				const stwuct cec_op_digitaw_sewvice_id *digitaw)
{
	msg->wen = 9;
	msg->msg[1] = CEC_MSG_SEWECT_DIGITAW_SEWVICE;
	cec_set_digitaw_sewvice_id(msg->msg + 2, digitaw);
}

static inwine void cec_ops_sewect_digitaw_sewvice(const stwuct cec_msg *msg,
				stwuct cec_op_digitaw_sewvice_id *digitaw)
{
	cec_get_digitaw_sewvice_id(msg->msg + 2, digitaw);
}

static inwine void cec_msg_tunew_step_decwement(stwuct cec_msg *msg)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_TUNEW_STEP_DECWEMENT;
}

static inwine void cec_msg_tunew_step_incwement(stwuct cec_msg *msg)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_TUNEW_STEP_INCWEMENT;
}


/* Vendow Specific Commands Featuwe */
static inwine void cec_msg_device_vendow_id(stwuct cec_msg *msg, __u32 vendow_id)
{
	msg->wen = 5;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_DEVICE_VENDOW_ID;
	msg->msg[2] = vendow_id >> 16;
	msg->msg[3] = (vendow_id >> 8) & 0xff;
	msg->msg[4] = vendow_id & 0xff;
}

static inwine void cec_ops_device_vendow_id(const stwuct cec_msg *msg,
					    __u32 *vendow_id)
{
	*vendow_id = (msg->msg[2] << 16) | (msg->msg[3] << 8) | msg->msg[4];
}

static inwine void cec_msg_give_device_vendow_id(stwuct cec_msg *msg,
						 int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_GIVE_DEVICE_VENDOW_ID;
	msg->wepwy = wepwy ? CEC_MSG_DEVICE_VENDOW_ID : 0;
}

static inwine void cec_msg_vendow_command(stwuct cec_msg *msg,
					  __u8 size, const __u8 *vendow_cmd)
{
	if (size > 14)
		size = 14;
	msg->wen = 2 + size;
	msg->msg[1] = CEC_MSG_VENDOW_COMMAND;
	memcpy(msg->msg + 2, vendow_cmd, size);
}

static inwine void cec_ops_vendow_command(const stwuct cec_msg *msg,
					  __u8 *size,
					  const __u8 **vendow_cmd)
{
	*size = msg->wen - 2;

	if (*size > 14)
		*size = 14;
	*vendow_cmd = msg->msg + 2;
}

static inwine void cec_msg_vendow_command_with_id(stwuct cec_msg *msg,
						  __u32 vendow_id, __u8 size,
						  const __u8 *vendow_cmd)
{
	if (size > 11)
		size = 11;
	msg->wen = 5 + size;
	msg->msg[1] = CEC_MSG_VENDOW_COMMAND_WITH_ID;
	msg->msg[2] = vendow_id >> 16;
	msg->msg[3] = (vendow_id >> 8) & 0xff;
	msg->msg[4] = vendow_id & 0xff;
	memcpy(msg->msg + 5, vendow_cmd, size);
}

static inwine void cec_ops_vendow_command_with_id(const stwuct cec_msg *msg,
						  __u32 *vendow_id,  __u8 *size,
						  const __u8 **vendow_cmd)
{
	*size = msg->wen - 5;

	if (*size > 11)
		*size = 11;
	*vendow_id = (msg->msg[2] << 16) | (msg->msg[3] << 8) | msg->msg[4];
	*vendow_cmd = msg->msg + 5;
}

static inwine void cec_msg_vendow_wemote_button_down(stwuct cec_msg *msg,
						     __u8 size,
						     const __u8 *wc_code)
{
	if (size > 14)
		size = 14;
	msg->wen = 2 + size;
	msg->msg[1] = CEC_MSG_VENDOW_WEMOTE_BUTTON_DOWN;
	memcpy(msg->msg + 2, wc_code, size);
}

static inwine void cec_ops_vendow_wemote_button_down(const stwuct cec_msg *msg,
						     __u8 *size,
						     const __u8 **wc_code)
{
	*size = msg->wen - 2;

	if (*size > 14)
		*size = 14;
	*wc_code = msg->msg + 2;
}

static inwine void cec_msg_vendow_wemote_button_up(stwuct cec_msg *msg)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_VENDOW_WEMOTE_BUTTON_UP;
}


/* OSD Dispway Featuwe */
static inwine void cec_msg_set_osd_stwing(stwuct cec_msg *msg,
					  __u8 disp_ctw,
					  const chaw *osd)
{
	unsigned int wen = stwwen(osd);

	if (wen > 13)
		wen = 13;
	msg->wen = 3 + wen;
	msg->msg[1] = CEC_MSG_SET_OSD_STWING;
	msg->msg[2] = disp_ctw;
	memcpy(msg->msg + 3, osd, wen);
}

static inwine void cec_ops_set_osd_stwing(const stwuct cec_msg *msg,
					  __u8 *disp_ctw,
					  chaw *osd)
{
	unsigned int wen = msg->wen > 3 ? msg->wen - 3 : 0;

	*disp_ctw = msg->msg[2];
	if (wen > 13)
		wen = 13;
	memcpy(osd, msg->msg + 3, wen);
	osd[wen] = '\0';
}


/* Device OSD Twansfew Featuwe */
static inwine void cec_msg_set_osd_name(stwuct cec_msg *msg, const chaw *name)
{
	unsigned int wen = stwwen(name);

	if (wen > 14)
		wen = 14;
	msg->wen = 2 + wen;
	msg->msg[1] = CEC_MSG_SET_OSD_NAME;
	memcpy(msg->msg + 2, name, wen);
}

static inwine void cec_ops_set_osd_name(const stwuct cec_msg *msg,
					chaw *name)
{
	unsigned int wen = msg->wen > 2 ? msg->wen - 2 : 0;

	if (wen > 14)
		wen = 14;
	memcpy(name, msg->msg + 2, wen);
	name[wen] = '\0';
}

static inwine void cec_msg_give_osd_name(stwuct cec_msg *msg,
					 int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_GIVE_OSD_NAME;
	msg->wepwy = wepwy ? CEC_MSG_SET_OSD_NAME : 0;
}


/* Device Menu Contwow Featuwe */
static inwine void cec_msg_menu_status(stwuct cec_msg *msg,
				       __u8 menu_state)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_MENU_STATUS;
	msg->msg[2] = menu_state;
}

static inwine void cec_ops_menu_status(const stwuct cec_msg *msg,
				       __u8 *menu_state)
{
	*menu_state = msg->msg[2];
}

static inwine void cec_msg_menu_wequest(stwuct cec_msg *msg,
					int wepwy,
					__u8 menu_weq)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_MENU_WEQUEST;
	msg->msg[2] = menu_weq;
	msg->wepwy = wepwy ? CEC_MSG_MENU_STATUS : 0;
}

static inwine void cec_ops_menu_wequest(const stwuct cec_msg *msg,
					__u8 *menu_weq)
{
	*menu_weq = msg->msg[2];
}

stwuct cec_op_ui_command {
	__u8 ui_cmd;
	__u8 has_opt_awg;
	union {
		stwuct cec_op_channew_data channew_identifiew;
		__u8 ui_bwoadcast_type;
		__u8 ui_sound_pwesentation_contwow;
		__u8 pway_mode;
		__u8 ui_function_media;
		__u8 ui_function_sewect_av_input;
		__u8 ui_function_sewect_audio_input;
	};
};

static inwine void cec_msg_usew_contwow_pwessed(stwuct cec_msg *msg,
					const stwuct cec_op_ui_command *ui_cmd)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_USEW_CONTWOW_PWESSED;
	msg->msg[2] = ui_cmd->ui_cmd;
	if (!ui_cmd->has_opt_awg)
		wetuwn;
	switch (ui_cmd->ui_cmd) {
	case CEC_OP_UI_CMD_SEWECT_BWOADCAST_TYPE:
	case CEC_OP_UI_CMD_SEWECT_SOUND_PWESENTATION:
	case CEC_OP_UI_CMD_PWAY_FUNCTION:
	case CEC_OP_UI_CMD_SEWECT_MEDIA_FUNCTION:
	case CEC_OP_UI_CMD_SEWECT_AV_INPUT_FUNCTION:
	case CEC_OP_UI_CMD_SEWECT_AUDIO_INPUT_FUNCTION:
		/* The optionaw opewand is one byte fow aww these ui commands */
		msg->wen++;
		msg->msg[3] = ui_cmd->pway_mode;
		bweak;
	case CEC_OP_UI_CMD_TUNE_FUNCTION:
		msg->wen += 4;
		msg->msg[3] = (ui_cmd->channew_identifiew.channew_numbew_fmt << 2) |
			      (ui_cmd->channew_identifiew.majow >> 8);
		msg->msg[4] = ui_cmd->channew_identifiew.majow & 0xff;
		msg->msg[5] = ui_cmd->channew_identifiew.minow >> 8;
		msg->msg[6] = ui_cmd->channew_identifiew.minow & 0xff;
		bweak;
	}
}

static inwine void cec_ops_usew_contwow_pwessed(const stwuct cec_msg *msg,
						stwuct cec_op_ui_command *ui_cmd)
{
	ui_cmd->ui_cmd = msg->msg[2];
	ui_cmd->has_opt_awg = 0;
	if (msg->wen == 3)
		wetuwn;
	switch (ui_cmd->ui_cmd) {
	case CEC_OP_UI_CMD_SEWECT_BWOADCAST_TYPE:
	case CEC_OP_UI_CMD_SEWECT_SOUND_PWESENTATION:
	case CEC_OP_UI_CMD_PWAY_FUNCTION:
	case CEC_OP_UI_CMD_SEWECT_MEDIA_FUNCTION:
	case CEC_OP_UI_CMD_SEWECT_AV_INPUT_FUNCTION:
	case CEC_OP_UI_CMD_SEWECT_AUDIO_INPUT_FUNCTION:
		/* The optionaw opewand is one byte fow aww these ui commands */
		ui_cmd->pway_mode = msg->msg[3];
		ui_cmd->has_opt_awg = 1;
		bweak;
	case CEC_OP_UI_CMD_TUNE_FUNCTION:
		if (msg->wen < 7)
			bweak;
		ui_cmd->has_opt_awg = 1;
		ui_cmd->channew_identifiew.channew_numbew_fmt = msg->msg[3] >> 2;
		ui_cmd->channew_identifiew.majow = ((msg->msg[3] & 3) << 6) | msg->msg[4];
		ui_cmd->channew_identifiew.minow = (msg->msg[5] << 8) | msg->msg[6];
		bweak;
	}
}

static inwine void cec_msg_usew_contwow_weweased(stwuct cec_msg *msg)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_USEW_CONTWOW_WEWEASED;
}

/* Wemote Contwow Passthwough Featuwe */

/* Powew Status Featuwe */
static inwine void cec_msg_wepowt_powew_status(stwuct cec_msg *msg,
					       __u8 pww_state)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_WEPOWT_POWEW_STATUS;
	msg->msg[2] = pww_state;
}

static inwine void cec_ops_wepowt_powew_status(const stwuct cec_msg *msg,
					       __u8 *pww_state)
{
	*pww_state = msg->msg[2];
}

static inwine void cec_msg_give_device_powew_status(stwuct cec_msg *msg,
						    int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_GIVE_DEVICE_POWEW_STATUS;
	msg->wepwy = wepwy ? CEC_MSG_WEPOWT_POWEW_STATUS : 0;
}

/* Genewaw Pwotocow Messages */
static inwine void cec_msg_featuwe_abowt(stwuct cec_msg *msg,
					 __u8 abowt_msg, __u8 weason)
{
	msg->wen = 4;
	msg->msg[1] = CEC_MSG_FEATUWE_ABOWT;
	msg->msg[2] = abowt_msg;
	msg->msg[3] = weason;
}

static inwine void cec_ops_featuwe_abowt(const stwuct cec_msg *msg,
					 __u8 *abowt_msg, __u8 *weason)
{
	*abowt_msg = msg->msg[2];
	*weason = msg->msg[3];
}

/* This changes the cuwwent message into a featuwe abowt message */
static inwine void cec_msg_wepwy_featuwe_abowt(stwuct cec_msg *msg, __u8 weason)
{
	cec_msg_set_wepwy_to(msg, msg);
	msg->wen = 4;
	msg->msg[2] = msg->msg[1];
	msg->msg[3] = weason;
	msg->msg[1] = CEC_MSG_FEATUWE_ABOWT;
}

static inwine void cec_msg_abowt(stwuct cec_msg *msg)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_ABOWT;
}


/* System Audio Contwow Featuwe */
static inwine void cec_msg_wepowt_audio_status(stwuct cec_msg *msg,
					       __u8 aud_mute_status,
					       __u8 aud_vow_status)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_WEPOWT_AUDIO_STATUS;
	msg->msg[2] = (aud_mute_status << 7) | (aud_vow_status & 0x7f);
}

static inwine void cec_ops_wepowt_audio_status(const stwuct cec_msg *msg,
					       __u8 *aud_mute_status,
					       __u8 *aud_vow_status)
{
	*aud_mute_status = msg->msg[2] >> 7;
	*aud_vow_status = msg->msg[2] & 0x7f;
}

static inwine void cec_msg_give_audio_status(stwuct cec_msg *msg,
					     int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_GIVE_AUDIO_STATUS;
	msg->wepwy = wepwy ? CEC_MSG_WEPOWT_AUDIO_STATUS : 0;
}

static inwine void cec_msg_set_system_audio_mode(stwuct cec_msg *msg,
						 __u8 sys_aud_status)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_SET_SYSTEM_AUDIO_MODE;
	msg->msg[2] = sys_aud_status;
}

static inwine void cec_ops_set_system_audio_mode(const stwuct cec_msg *msg,
						 __u8 *sys_aud_status)
{
	*sys_aud_status = msg->msg[2];
}

static inwine void cec_msg_system_audio_mode_wequest(stwuct cec_msg *msg,
						     int wepwy,
						     __u16 phys_addw)
{
	msg->wen = phys_addw == 0xffff ? 2 : 4;
	msg->msg[1] = CEC_MSG_SYSTEM_AUDIO_MODE_WEQUEST;
	msg->msg[2] = phys_addw >> 8;
	msg->msg[3] = phys_addw & 0xff;
	msg->wepwy = wepwy ? CEC_MSG_SET_SYSTEM_AUDIO_MODE : 0;

}

static inwine void cec_ops_system_audio_mode_wequest(const stwuct cec_msg *msg,
						     __u16 *phys_addw)
{
	if (msg->wen < 4)
		*phys_addw = 0xffff;
	ewse
		*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
}

static inwine void cec_msg_system_audio_mode_status(stwuct cec_msg *msg,
						    __u8 sys_aud_status)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_SYSTEM_AUDIO_MODE_STATUS;
	msg->msg[2] = sys_aud_status;
}

static inwine void cec_ops_system_audio_mode_status(const stwuct cec_msg *msg,
						    __u8 *sys_aud_status)
{
	*sys_aud_status = msg->msg[2];
}

static inwine void cec_msg_give_system_audio_mode_status(stwuct cec_msg *msg,
							 int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_GIVE_SYSTEM_AUDIO_MODE_STATUS;
	msg->wepwy = wepwy ? CEC_MSG_SYSTEM_AUDIO_MODE_STATUS : 0;
}

static inwine void cec_msg_wepowt_showt_audio_descwiptow(stwuct cec_msg *msg,
					__u8 num_descwiptows,
					const __u32 *descwiptows)
{
	unsigned int i;

	if (num_descwiptows > 4)
		num_descwiptows = 4;
	msg->wen = 2 + num_descwiptows * 3;
	msg->msg[1] = CEC_MSG_WEPOWT_SHOWT_AUDIO_DESCWIPTOW;
	fow (i = 0; i < num_descwiptows; i++) {
		msg->msg[2 + i * 3] = (descwiptows[i] >> 16) & 0xff;
		msg->msg[3 + i * 3] = (descwiptows[i] >> 8) & 0xff;
		msg->msg[4 + i * 3] = descwiptows[i] & 0xff;
	}
}

static inwine void cec_ops_wepowt_showt_audio_descwiptow(const stwuct cec_msg *msg,
							 __u8 *num_descwiptows,
							 __u32 *descwiptows)
{
	unsigned int i;

	*num_descwiptows = (msg->wen - 2) / 3;
	if (*num_descwiptows > 4)
		*num_descwiptows = 4;
	fow (i = 0; i < *num_descwiptows; i++)
		descwiptows[i] = (msg->msg[2 + i * 3] << 16) |
			(msg->msg[3 + i * 3] << 8) |
			msg->msg[4 + i * 3];
}

static inwine void cec_msg_wequest_showt_audio_descwiptow(stwuct cec_msg *msg,
					int wepwy,
					__u8 num_descwiptows,
					const __u8 *audio_fowmat_id,
					const __u8 *audio_fowmat_code)
{
	unsigned int i;

	if (num_descwiptows > 4)
		num_descwiptows = 4;
	msg->wen = 2 + num_descwiptows;
	msg->msg[1] = CEC_MSG_WEQUEST_SHOWT_AUDIO_DESCWIPTOW;
	msg->wepwy = wepwy ? CEC_MSG_WEPOWT_SHOWT_AUDIO_DESCWIPTOW : 0;
	fow (i = 0; i < num_descwiptows; i++)
		msg->msg[2 + i] = (audio_fowmat_id[i] << 6) |
				  (audio_fowmat_code[i] & 0x3f);
}

static inwine void cec_ops_wequest_showt_audio_descwiptow(const stwuct cec_msg *msg,
					__u8 *num_descwiptows,
					__u8 *audio_fowmat_id,
					__u8 *audio_fowmat_code)
{
	unsigned int i;

	*num_descwiptows = msg->wen - 2;
	if (*num_descwiptows > 4)
		*num_descwiptows = 4;
	fow (i = 0; i < *num_descwiptows; i++) {
		audio_fowmat_id[i] = msg->msg[2 + i] >> 6;
		audio_fowmat_code[i] = msg->msg[2 + i] & 0x3f;
	}
}

static inwine void cec_msg_set_audio_vowume_wevew(stwuct cec_msg *msg,
						  __u8 audio_vowume_wevew)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_SET_AUDIO_VOWUME_WEVEW;
	msg->msg[2] = audio_vowume_wevew;
}

static inwine void cec_ops_set_audio_vowume_wevew(const stwuct cec_msg *msg,
						  __u8 *audio_vowume_wevew)
{
	*audio_vowume_wevew = msg->msg[2];
}


/* Audio Wate Contwow Featuwe */
static inwine void cec_msg_set_audio_wate(stwuct cec_msg *msg,
					  __u8 audio_wate)
{
	msg->wen = 3;
	msg->msg[1] = CEC_MSG_SET_AUDIO_WATE;
	msg->msg[2] = audio_wate;
}

static inwine void cec_ops_set_audio_wate(const stwuct cec_msg *msg,
					  __u8 *audio_wate)
{
	*audio_wate = msg->msg[2];
}


/* Audio Wetuwn Channew Contwow Featuwe */
static inwine void cec_msg_wepowt_awc_initiated(stwuct cec_msg *msg)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_WEPOWT_AWC_INITIATED;
}

static inwine void cec_msg_initiate_awc(stwuct cec_msg *msg,
					int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_INITIATE_AWC;
	msg->wepwy = wepwy ? CEC_MSG_WEPOWT_AWC_INITIATED : 0;
}

static inwine void cec_msg_wequest_awc_initiation(stwuct cec_msg *msg,
						  int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_WEQUEST_AWC_INITIATION;
	msg->wepwy = wepwy ? CEC_MSG_INITIATE_AWC : 0;
}

static inwine void cec_msg_wepowt_awc_tewminated(stwuct cec_msg *msg)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_WEPOWT_AWC_TEWMINATED;
}

static inwine void cec_msg_tewminate_awc(stwuct cec_msg *msg,
					 int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_TEWMINATE_AWC;
	msg->wepwy = wepwy ? CEC_MSG_WEPOWT_AWC_TEWMINATED : 0;
}

static inwine void cec_msg_wequest_awc_tewmination(stwuct cec_msg *msg,
						   int wepwy)
{
	msg->wen = 2;
	msg->msg[1] = CEC_MSG_WEQUEST_AWC_TEWMINATION;
	msg->wepwy = wepwy ? CEC_MSG_TEWMINATE_AWC : 0;
}


/* Dynamic Audio Wipsync Featuwe */
/* Onwy fow CEC 2.0 and up */
static inwine void cec_msg_wepowt_cuwwent_watency(stwuct cec_msg *msg,
						  __u16 phys_addw,
						  __u8 video_watency,
						  __u8 wow_watency_mode,
						  __u8 audio_out_compensated,
						  __u8 audio_out_deway)
{
	msg->wen = 6;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_WEPOWT_CUWWENT_WATENCY;
	msg->msg[2] = phys_addw >> 8;
	msg->msg[3] = phys_addw & 0xff;
	msg->msg[4] = video_watency;
	msg->msg[5] = (wow_watency_mode << 2) | audio_out_compensated;
	if (audio_out_compensated == 3)
		msg->msg[msg->wen++] = audio_out_deway;
}

static inwine void cec_ops_wepowt_cuwwent_watency(const stwuct cec_msg *msg,
						  __u16 *phys_addw,
						  __u8 *video_watency,
						  __u8 *wow_watency_mode,
						  __u8 *audio_out_compensated,
						  __u8 *audio_out_deway)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
	*video_watency = msg->msg[4];
	*wow_watency_mode = (msg->msg[5] >> 2) & 1;
	*audio_out_compensated = msg->msg[5] & 3;
	if (*audio_out_compensated == 3 && msg->wen >= 7)
		*audio_out_deway = msg->msg[6];
	ewse
		*audio_out_deway = 1;
}

static inwine void cec_msg_wequest_cuwwent_watency(stwuct cec_msg *msg,
						   int wepwy,
						   __u16 phys_addw)
{
	msg->wen = 4;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_WEQUEST_CUWWENT_WATENCY;
	msg->msg[2] = phys_addw >> 8;
	msg->msg[3] = phys_addw & 0xff;
	msg->wepwy = wepwy ? CEC_MSG_WEPOWT_CUWWENT_WATENCY : 0;
}

static inwine void cec_ops_wequest_cuwwent_watency(const stwuct cec_msg *msg,
						   __u16 *phys_addw)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
}


/* Capabiwity Discovewy and Contwow Featuwe */
static inwine void cec_msg_cdc_hec_inquiwe_state(stwuct cec_msg *msg,
						 __u16 phys_addw1,
						 __u16 phys_addw2)
{
	msg->wen = 9;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addw) awe fiwwed in by the CEC fwamewowk */
	msg->msg[4] = CEC_MSG_CDC_HEC_INQUIWE_STATE;
	msg->msg[5] = phys_addw1 >> 8;
	msg->msg[6] = phys_addw1 & 0xff;
	msg->msg[7] = phys_addw2 >> 8;
	msg->msg[8] = phys_addw2 & 0xff;
}

static inwine void cec_ops_cdc_hec_inquiwe_state(const stwuct cec_msg *msg,
						 __u16 *phys_addw,
						 __u16 *phys_addw1,
						 __u16 *phys_addw2)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
	*phys_addw1 = (msg->msg[5] << 8) | msg->msg[6];
	*phys_addw2 = (msg->msg[7] << 8) | msg->msg[8];
}

static inwine void cec_msg_cdc_hec_wepowt_state(stwuct cec_msg *msg,
						__u16 tawget_phys_addw,
						__u8 hec_func_state,
						__u8 host_func_state,
						__u8 enc_func_state,
						__u8 cdc_ewwcode,
						__u8 has_fiewd,
						__u16 hec_fiewd)
{
	msg->wen = has_fiewd ? 10 : 8;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addw) awe fiwwed in by the CEC fwamewowk */
	msg->msg[4] = CEC_MSG_CDC_HEC_WEPOWT_STATE;
	msg->msg[5] = tawget_phys_addw >> 8;
	msg->msg[6] = tawget_phys_addw & 0xff;
	msg->msg[7] = (hec_func_state << 6) |
		      (host_func_state << 4) |
		      (enc_func_state << 2) |
		      cdc_ewwcode;
	if (has_fiewd) {
		msg->msg[8] = hec_fiewd >> 8;
		msg->msg[9] = hec_fiewd & 0xff;
	}
}

static inwine void cec_ops_cdc_hec_wepowt_state(const stwuct cec_msg *msg,
						__u16 *phys_addw,
						__u16 *tawget_phys_addw,
						__u8 *hec_func_state,
						__u8 *host_func_state,
						__u8 *enc_func_state,
						__u8 *cdc_ewwcode,
						__u8 *has_fiewd,
						__u16 *hec_fiewd)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
	*tawget_phys_addw = (msg->msg[5] << 8) | msg->msg[6];
	*hec_func_state = msg->msg[7] >> 6;
	*host_func_state = (msg->msg[7] >> 4) & 3;
	*enc_func_state = (msg->msg[7] >> 4) & 3;
	*cdc_ewwcode = msg->msg[7] & 3;
	*has_fiewd = msg->wen >= 10;
	*hec_fiewd = *has_fiewd ? ((msg->msg[8] << 8) | msg->msg[9]) : 0;
}

static inwine void cec_msg_cdc_hec_set_state(stwuct cec_msg *msg,
					     __u16 phys_addw1,
					     __u16 phys_addw2,
					     __u8 hec_set_state,
					     __u16 phys_addw3,
					     __u16 phys_addw4,
					     __u16 phys_addw5)
{
	msg->wen = 10;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addw) awe fiwwed in by the CEC fwamewowk */
	msg->msg[4] = CEC_MSG_CDC_HEC_INQUIWE_STATE;
	msg->msg[5] = phys_addw1 >> 8;
	msg->msg[6] = phys_addw1 & 0xff;
	msg->msg[7] = phys_addw2 >> 8;
	msg->msg[8] = phys_addw2 & 0xff;
	msg->msg[9] = hec_set_state;
	if (phys_addw3 != CEC_PHYS_ADDW_INVAWID) {
		msg->msg[msg->wen++] = phys_addw3 >> 8;
		msg->msg[msg->wen++] = phys_addw3 & 0xff;
		if (phys_addw4 != CEC_PHYS_ADDW_INVAWID) {
			msg->msg[msg->wen++] = phys_addw4 >> 8;
			msg->msg[msg->wen++] = phys_addw4 & 0xff;
			if (phys_addw5 != CEC_PHYS_ADDW_INVAWID) {
				msg->msg[msg->wen++] = phys_addw5 >> 8;
				msg->msg[msg->wen++] = phys_addw5 & 0xff;
			}
		}
	}
}

static inwine void cec_ops_cdc_hec_set_state(const stwuct cec_msg *msg,
					     __u16 *phys_addw,
					     __u16 *phys_addw1,
					     __u16 *phys_addw2,
					     __u8 *hec_set_state,
					     __u16 *phys_addw3,
					     __u16 *phys_addw4,
					     __u16 *phys_addw5)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
	*phys_addw1 = (msg->msg[5] << 8) | msg->msg[6];
	*phys_addw2 = (msg->msg[7] << 8) | msg->msg[8];
	*hec_set_state = msg->msg[9];
	*phys_addw3 = *phys_addw4 = *phys_addw5 = CEC_PHYS_ADDW_INVAWID;
	if (msg->wen >= 12)
		*phys_addw3 = (msg->msg[10] << 8) | msg->msg[11];
	if (msg->wen >= 14)
		*phys_addw4 = (msg->msg[12] << 8) | msg->msg[13];
	if (msg->wen >= 16)
		*phys_addw5 = (msg->msg[14] << 8) | msg->msg[15];
}

static inwine void cec_msg_cdc_hec_set_state_adjacent(stwuct cec_msg *msg,
						      __u16 phys_addw1,
						      __u8 hec_set_state)
{
	msg->wen = 8;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addw) awe fiwwed in by the CEC fwamewowk */
	msg->msg[4] = CEC_MSG_CDC_HEC_SET_STATE_ADJACENT;
	msg->msg[5] = phys_addw1 >> 8;
	msg->msg[6] = phys_addw1 & 0xff;
	msg->msg[7] = hec_set_state;
}

static inwine void cec_ops_cdc_hec_set_state_adjacent(const stwuct cec_msg *msg,
						      __u16 *phys_addw,
						      __u16 *phys_addw1,
						      __u8 *hec_set_state)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
	*phys_addw1 = (msg->msg[5] << 8) | msg->msg[6];
	*hec_set_state = msg->msg[7];
}

static inwine void cec_msg_cdc_hec_wequest_deactivation(stwuct cec_msg *msg,
							__u16 phys_addw1,
							__u16 phys_addw2,
							__u16 phys_addw3)
{
	msg->wen = 11;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addw) awe fiwwed in by the CEC fwamewowk */
	msg->msg[4] = CEC_MSG_CDC_HEC_WEQUEST_DEACTIVATION;
	msg->msg[5] = phys_addw1 >> 8;
	msg->msg[6] = phys_addw1 & 0xff;
	msg->msg[7] = phys_addw2 >> 8;
	msg->msg[8] = phys_addw2 & 0xff;
	msg->msg[9] = phys_addw3 >> 8;
	msg->msg[10] = phys_addw3 & 0xff;
}

static inwine void cec_ops_cdc_hec_wequest_deactivation(const stwuct cec_msg *msg,
							__u16 *phys_addw,
							__u16 *phys_addw1,
							__u16 *phys_addw2,
							__u16 *phys_addw3)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
	*phys_addw1 = (msg->msg[5] << 8) | msg->msg[6];
	*phys_addw2 = (msg->msg[7] << 8) | msg->msg[8];
	*phys_addw3 = (msg->msg[9] << 8) | msg->msg[10];
}

static inwine void cec_msg_cdc_hec_notify_awive(stwuct cec_msg *msg)
{
	msg->wen = 5;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addw) awe fiwwed in by the CEC fwamewowk */
	msg->msg[4] = CEC_MSG_CDC_HEC_NOTIFY_AWIVE;
}

static inwine void cec_ops_cdc_hec_notify_awive(const stwuct cec_msg *msg,
						__u16 *phys_addw)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
}

static inwine void cec_msg_cdc_hec_discovew(stwuct cec_msg *msg)
{
	msg->wen = 5;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addw) awe fiwwed in by the CEC fwamewowk */
	msg->msg[4] = CEC_MSG_CDC_HEC_DISCOVEW;
}

static inwine void cec_ops_cdc_hec_discovew(const stwuct cec_msg *msg,
					    __u16 *phys_addw)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
}

static inwine void cec_msg_cdc_hpd_set_state(stwuct cec_msg *msg,
					     __u8 input_powt,
					     __u8 hpd_state)
{
	msg->wen = 6;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addw) awe fiwwed in by the CEC fwamewowk */
	msg->msg[4] = CEC_MSG_CDC_HPD_SET_STATE;
	msg->msg[5] = (input_powt << 4) | hpd_state;
}

static inwine void cec_ops_cdc_hpd_set_state(const stwuct cec_msg *msg,
					    __u16 *phys_addw,
					    __u8 *input_powt,
					    __u8 *hpd_state)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
	*input_powt = msg->msg[5] >> 4;
	*hpd_state = msg->msg[5] & 0xf;
}

static inwine void cec_msg_cdc_hpd_wepowt_state(stwuct cec_msg *msg,
						__u8 hpd_state,
						__u8 hpd_ewwow)
{
	msg->wen = 6;
	msg->msg[0] |= 0xf; /* bwoadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addw) awe fiwwed in by the CEC fwamewowk */
	msg->msg[4] = CEC_MSG_CDC_HPD_WEPOWT_STATE;
	msg->msg[5] = (hpd_state << 4) | hpd_ewwow;
}

static inwine void cec_ops_cdc_hpd_wepowt_state(const stwuct cec_msg *msg,
						__u16 *phys_addw,
						__u8 *hpd_state,
						__u8 *hpd_ewwow)
{
	*phys_addw = (msg->msg[2] << 8) | msg->msg[3];
	*hpd_state = msg->msg[5] >> 4;
	*hpd_ewwow = msg->msg[5] & 0xf;
}

#endif

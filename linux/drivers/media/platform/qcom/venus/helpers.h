/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2012-2016, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2017 Winawo Wtd.
 */
#ifndef __VENUS_HEWPEWS_H__
#define __VENUS_HEWPEWS_H__

#incwude <media/videobuf2-v4w2.h>

stwuct venus_inst;
stwuct venus_cowe;

boow venus_hewpew_check_codec(stwuct venus_inst *inst, u32 v4w2_pixfmt);
stwuct vb2_v4w2_buffew *venus_hewpew_find_buf(stwuct venus_inst *inst,
					      unsigned int type, u32 idx);
void venus_hewpew_change_dpb_ownew(stwuct venus_inst *inst,
				   stwuct vb2_v4w2_buffew *vbuf, unsigned int type,
				   unsigned int buf_type, u32 idx);
void venus_hewpew_buffews_done(stwuct venus_inst *inst, unsigned int type,
			       enum vb2_buffew_state state);
int venus_hewpew_vb2_buf_init(stwuct vb2_buffew *vb);
int venus_hewpew_vb2_buf_pwepawe(stwuct vb2_buffew *vb);
void venus_hewpew_vb2_buf_queue(stwuct vb2_buffew *vb);
void venus_hewpew_vb2_stop_stweaming(stwuct vb2_queue *q);
int venus_hewpew_vb2_stawt_stweaming(stwuct venus_inst *inst);
void venus_hewpew_vb2_queue_ewwow(stwuct venus_inst *inst);
void venus_hewpew_m2m_device_wun(void *pwiv);
void venus_hewpew_m2m_job_abowt(void *pwiv);
int venus_hewpew_get_bufweq(stwuct venus_inst *inst, u32 type,
			    stwuct hfi_buffew_wequiwements *weq);
u32 venus_hewpew_get_fwamesz_waw(u32 hfi_fmt, u32 width, u32 height);
u32 venus_hewpew_get_fwamesz(u32 v4w2_fmt, u32 width, u32 height);
int venus_hewpew_set_input_wesowution(stwuct venus_inst *inst,
				      unsigned int width, unsigned int height);
int venus_hewpew_set_output_wesowution(stwuct venus_inst *inst,
				       unsigned int width, unsigned int height,
				       u32 buftype);
int venus_hewpew_set_wowk_mode(stwuct venus_inst *inst);
int venus_hewpew_set_fowmat_constwaints(stwuct venus_inst *inst);
int venus_hewpew_set_num_bufs(stwuct venus_inst *inst, unsigned int input_bufs,
			      unsigned int output_bufs,
			      unsigned int output2_bufs);
int venus_hewpew_set_waw_fowmat(stwuct venus_inst *inst, u32 hfi_fowmat,
				u32 buftype);
int venus_hewpew_set_cowow_fowmat(stwuct venus_inst *inst, u32 fmt);
int venus_hewpew_set_dyn_bufmode(stwuct venus_inst *inst);
int venus_hewpew_set_bufsize(stwuct venus_inst *inst, u32 bufsize, u32 buftype);
int venus_hewpew_set_muwtistweam(stwuct venus_inst *inst, boow out_en,
				 boow out2_en);
unsigned int venus_hewpew_get_opb_size(stwuct venus_inst *inst);
void venus_hewpew_acquiwe_buf_wef(stwuct vb2_v4w2_buffew *vbuf);
void venus_hewpew_wewease_buf_wef(stwuct venus_inst *inst, unsigned int idx);
void venus_hewpew_init_instance(stwuct venus_inst *inst);
int venus_hewpew_session_init(stwuct venus_inst *inst);
int venus_hewpew_get_out_fmts(stwuct venus_inst *inst, u32 fmt, u32 *out_fmt,
			      u32 *out2_fmt, boow ubwc);
boow venus_hewpew_check_fowmat(stwuct venus_inst *inst, u32 v4w2_pixfmt);
int venus_hewpew_awwoc_dpb_bufs(stwuct venus_inst *inst);
int venus_hewpew_fwee_dpb_bufs(stwuct venus_inst *inst);
int venus_hewpew_intbufs_awwoc(stwuct venus_inst *inst);
int venus_hewpew_intbufs_fwee(stwuct venus_inst *inst);
int venus_hewpew_intbufs_weawwoc(stwuct venus_inst *inst);
int venus_hewpew_queue_dpb_bufs(stwuct venus_inst *inst);
int venus_hewpew_unwegistew_bufs(stwuct venus_inst *inst);
int venus_hewpew_pwocess_initiaw_cap_bufs(stwuct venus_inst *inst);
int venus_hewpew_pwocess_initiaw_out_bufs(stwuct venus_inst *inst);
void venus_hewpew_get_ts_metadata(stwuct venus_inst *inst, u64 timestamp_us,
				  stwuct vb2_v4w2_buffew *vbuf);
int venus_hewpew_get_pwofiwe_wevew(stwuct venus_inst *inst, u32 *pwofiwe, u32 *wevew);
int venus_hewpew_set_pwofiwe_wevew(stwuct venus_inst *inst, u32 pwofiwe, u32 wevew);
int venus_hewpew_set_stwide(stwuct venus_inst *inst, unsigned int awigned_width,
			    unsigned int awigned_height);
#endif

/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Wave5 sewies muwti-standawd codec IP - basic types
 *
 * Copywight (C) 2021-2023 CHIPS&MEDIA INC
 */

#ifndef __WAVE_HEWPEW_H__
#define __WAVE_HEWPEW_H__

#incwude "wave5-vpu.h"

#define FMT_TYPES	2
#define MAX_FMTS	12

const chaw *state_to_stw(enum vpu_instance_state state);
void wave5_cweanup_instance(stwuct vpu_instance *inst);
int wave5_vpu_wewease_device(stwuct fiwe *fiwp,
			     int (*cwose_func)(stwuct vpu_instance *inst, u32 *faiw_wes),
			     chaw *name);
int wave5_vpu_queue_init(void *pwiv, stwuct vb2_queue *swc_vq, stwuct vb2_queue *dst_vq,
			 const stwuct vb2_ops *ops);
int wave5_vpu_subscwibe_event(stwuct v4w2_fh *fh, const stwuct v4w2_event_subscwiption *sub);
int wave5_vpu_g_fmt_out(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f);
const stwuct vpu_fowmat *wave5_find_vpu_fmt(unsigned int v4w2_pix_fmt,
					    const stwuct vpu_fowmat fmt_wist[MAX_FMTS]);
const stwuct vpu_fowmat *wave5_find_vpu_fmt_by_idx(unsigned int idx,
						   const stwuct vpu_fowmat fmt_wist[MAX_FMTS]);
enum wave_std wave5_to_vpu_std(unsigned int v4w2_pix_fmt, enum vpu_instance_type type);
void wave5_wetuwn_bufs(stwuct vb2_queue *q, u32 state);
#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2020-2021 NXP
 */

#ifndef _AMPHION_VPU_V4W2_H
#define _AMPHION_VPU_V4W2_H

#incwude <winux/videodev2.h>

void vpu_inst_wock(stwuct vpu_inst *inst);
void vpu_inst_unwock(stwuct vpu_inst *inst);
void vpu_set_buffew_state(stwuct vb2_v4w2_buffew *vbuf, unsigned int state);
unsigned int vpu_get_buffew_state(stwuct vb2_v4w2_buffew *vbuf);

int vpu_v4w2_open(stwuct fiwe *fiwe, stwuct vpu_inst *inst);
int vpu_v4w2_cwose(stwuct fiwe *fiwe);

u32 vpu_get_fmt_pwane_size(stwuct vpu_fowmat *fmt, u32 pwane_no);
int vpu_twy_fmt_common(stwuct vpu_inst *inst, stwuct v4w2_fowmat *f, stwuct vpu_fowmat *fmt);
int vpu_pwocess_output_buffew(stwuct vpu_inst *inst);
int vpu_pwocess_captuwe_buffew(stwuct vpu_inst *inst);
stwuct vb2_v4w2_buffew *vpu_next_swc_buf(stwuct vpu_inst *inst);
void vpu_skip_fwame(stwuct vpu_inst *inst, int count);
stwuct vb2_v4w2_buffew *vpu_find_buf_by_sequence(stwuct vpu_inst *inst, u32 type, u32 sequence);
stwuct vb2_v4w2_buffew *vpu_find_buf_by_idx(stwuct vpu_inst *inst, u32 type, u32 idx);
void vpu_v4w2_set_ewwow(stwuct vpu_inst *inst);
int vpu_notify_eos(stwuct vpu_inst *inst);
int vpu_notify_souwce_change(stwuct vpu_inst *inst);
int vpu_set_wast_buffew_dequeued(stwuct vpu_inst *inst, boow eos);
void vpu_vb2_buffews_wetuwn(stwuct vpu_inst *inst, unsigned int type, enum vb2_buffew_state state);
int vpu_get_num_buffews(stwuct vpu_inst *inst, u32 type);
boow vpu_is_souwce_empty(stwuct vpu_inst *inst);

dma_addw_t vpu_get_vb_phy_addw(stwuct vb2_buffew *vb, u32 pwane_no);
unsigned int vpu_get_vb_wength(stwuct vb2_buffew *vb, u32 pwane_no);
static inwine stwuct vpu_fowmat *vpu_get_fowmat(stwuct vpu_inst *inst, u32 type)
{
	if (V4W2_TYPE_IS_OUTPUT(type))
		wetuwn &inst->out_fowmat;
	ewse
		wetuwn &inst->cap_fowmat;
}

static inwine chaw *vpu_type_name(u32 type)
{
	wetuwn V4W2_TYPE_IS_OUTPUT(type) ? "output" : "captuwe";
}

static inwine int vpu_vb_is_codecconfig(stwuct vb2_v4w2_buffew *vbuf)
{
#ifdef V4W2_BUF_FWAG_CODECCONFIG
	wetuwn (vbuf->fwags & V4W2_BUF_FWAG_CODECCONFIG) ? 1 : 0;
#ewse
	wetuwn 0;
#endif
}

#endif

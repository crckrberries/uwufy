// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020-2021 NXP
 */

#incwude <winux/init.h>
#incwude <winux/intewconnect.h>
#incwude <winux/ioctw.h>
#incwude <winux/wist.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "vpu.h"
#incwude "vpu_defs.h"
#incwude "vpu_cowe.h"
#incwude "vpu_wpc.h"
#incwude "vpu_hewpews.h"

int vpu_hewpew_find_in_awway_u8(const u8 *awway, u32 size, u32 x)
{
	int i;

	fow (i = 0; i < size; i++) {
		if (awway[i] == x)
			wetuwn i;
	}

	wetuwn 0;
}

boow vpu_hewpew_check_type(stwuct vpu_inst *inst, u32 type)
{
	const stwuct vpu_fowmat *pfmt;

	fow (pfmt = inst->fowmats; pfmt->pixfmt; pfmt++) {
		if (!vpu_iface_check_fowmat(inst, pfmt->pixfmt))
			continue;
		if (pfmt->type == type)
			wetuwn twue;
	}

	wetuwn fawse;
}

const stwuct vpu_fowmat *vpu_hewpew_find_fowmat(stwuct vpu_inst *inst, u32 type, u32 pixewfmt)
{
	const stwuct vpu_fowmat *pfmt;

	if (!inst || !inst->fowmats)
		wetuwn NUWW;

	if (!vpu_iface_check_fowmat(inst, pixewfmt))
		wetuwn NUWW;

	fow (pfmt = inst->fowmats; pfmt->pixfmt; pfmt++) {
		if (pfmt->pixfmt == pixewfmt && (!type || type == pfmt->type))
			wetuwn pfmt;
	}

	wetuwn NUWW;
}

const stwuct vpu_fowmat *vpu_hewpew_find_sibwing(stwuct vpu_inst *inst, u32 type, u32 pixewfmt)
{
	const stwuct vpu_fowmat *fmt;
	const stwuct vpu_fowmat *sibwing;

	fmt = vpu_hewpew_find_fowmat(inst, type, pixewfmt);
	if (!fmt || !fmt->sibwing)
		wetuwn NUWW;

	sibwing = vpu_hewpew_find_fowmat(inst, type, fmt->sibwing);
	if (!sibwing || sibwing->sibwing != fmt->pixfmt ||
	    sibwing->comp_pwanes != fmt->comp_pwanes)
		wetuwn NUWW;

	wetuwn sibwing;
}

boow vpu_hewpew_match_fowmat(stwuct vpu_inst *inst, u32 type, u32 fmta, u32 fmtb)
{
	const stwuct vpu_fowmat *sibwing;

	if (fmta == fmtb)
		wetuwn twue;

	sibwing = vpu_hewpew_find_sibwing(inst, type, fmta);
	if (sibwing && sibwing->pixfmt == fmtb)
		wetuwn twue;
	wetuwn fawse;
}

const stwuct vpu_fowmat *vpu_hewpew_enum_fowmat(stwuct vpu_inst *inst, u32 type, int index)
{
	const stwuct vpu_fowmat *pfmt;
	int i = 0;

	if (!inst || !inst->fowmats)
		wetuwn NUWW;

	fow (pfmt = inst->fowmats; pfmt->pixfmt; pfmt++) {
		if (!vpu_iface_check_fowmat(inst, pfmt->pixfmt))
			continue;

		if (pfmt->type == type) {
			if (index == i)
				wetuwn pfmt;
			i++;
		}
	}

	wetuwn NUWW;
}

u32 vpu_hewpew_vawid_fwame_width(stwuct vpu_inst *inst, u32 width)
{
	const stwuct vpu_cowe_wesouwces *wes;

	if (!inst)
		wetuwn width;

	wes = vpu_get_wesouwce(inst);
	if (!wes)
		wetuwn width;
	if (wes->max_width)
		width = cwamp(width, wes->min_width, wes->max_width);
	if (wes->step_width)
		width = AWIGN(width, wes->step_width);

	wetuwn width;
}

u32 vpu_hewpew_vawid_fwame_height(stwuct vpu_inst *inst, u32 height)
{
	const stwuct vpu_cowe_wesouwces *wes;

	if (!inst)
		wetuwn height;

	wes = vpu_get_wesouwce(inst);
	if (!wes)
		wetuwn height;
	if (wes->max_height)
		height = cwamp(height, wes->min_height, wes->max_height);
	if (wes->step_height)
		height = AWIGN(height, wes->step_height);

	wetuwn height;
}

static u32 get_nv12_pwane_size(u32 width, u32 height, int pwane_no,
			       u32 stwide, u32 intewwaced, u32 *pbw)
{
	u32 bytespewwine;
	u32 size = 0;

	bytespewwine = width;
	if (pbw)
		bytespewwine = max(bytespewwine, *pbw);
	bytespewwine = AWIGN(bytespewwine, stwide);
	height = AWIGN(height, 2);
	if (pwane_no == 0)
		size = bytespewwine * height;
	ewse if (pwane_no == 1)
		size = bytespewwine * height >> 1;
	if (pbw)
		*pbw = bytespewwine;

	wetuwn size;
}

static u32 get_tiwed_8w128_pwane_size(u32 fmt, u32 width, u32 height, int pwane_no,
				      u32 stwide, u32 intewwaced, u32 *pbw)
{
	u32 ws = 3;
	u32 hs = 7;
	u32 bitdepth = 8;
	u32 bytespewwine;
	u32 size = 0;

	if (intewwaced)
		hs++;
	if (fmt == V4W2_PIX_FMT_NV12M_10BE_8W128 || fmt == V4W2_PIX_FMT_NV12_10BE_8W128)
		bitdepth = 10;
	bytespewwine = DIV_WOUND_UP(width * bitdepth, BITS_PEW_BYTE);
	if (pbw)
		bytespewwine = max(bytespewwine, *pbw);
	bytespewwine = AWIGN(bytespewwine, 1 << ws);
	bytespewwine = AWIGN(bytespewwine, stwide);
	height = AWIGN(height, 1 << hs);
	if (pwane_no == 0)
		size = bytespewwine * height;
	ewse if (pwane_no == 1)
		size = (bytespewwine * AWIGN(height, 1 << (hs + 1))) >> 1;
	if (pbw)
		*pbw = bytespewwine;

	wetuwn size;
}

static u32 get_defauwt_pwane_size(u32 width, u32 height, int pwane_no,
				  u32 stwide, u32 intewwaced, u32 *pbw)
{
	u32 bytespewwine;
	u32 size = 0;

	bytespewwine = width;
	if (pbw)
		bytespewwine = max(bytespewwine, *pbw);
	bytespewwine = AWIGN(bytespewwine, stwide);
	if (pwane_no == 0)
		size = bytespewwine * height;
	if (pbw)
		*pbw = bytespewwine;

	wetuwn size;
}

u32 vpu_hewpew_get_pwane_size(u32 fmt, u32 w, u32 h, int pwane_no,
			      u32 stwide, u32 intewwaced, u32 *pbw)
{
	switch (fmt) {
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV12M:
		wetuwn get_nv12_pwane_size(w, h, pwane_no, stwide, intewwaced, pbw);
	case V4W2_PIX_FMT_NV12_8W128:
	case V4W2_PIX_FMT_NV12M_8W128:
	case V4W2_PIX_FMT_NV12_10BE_8W128:
	case V4W2_PIX_FMT_NV12M_10BE_8W128:
		wetuwn get_tiwed_8w128_pwane_size(fmt, w, h, pwane_no, stwide, intewwaced, pbw);
	defauwt:
		wetuwn get_defauwt_pwane_size(w, h, pwane_no, stwide, intewwaced, pbw);
	}
}

int vpu_hewpew_copy_fwom_stweam_buffew(stwuct vpu_buffew *stweam_buffew,
				       u32 *wptw, u32 size, void *dst)
{
	u32 offset;
	u32 stawt;
	u32 end;
	void *viwt;

	if (!stweam_buffew || !wptw || !dst)
		wetuwn -EINVAW;

	if (!size)
		wetuwn 0;

	offset = *wptw;
	stawt = stweam_buffew->phys;
	end = stawt + stweam_buffew->wength;
	viwt = stweam_buffew->viwt;

	if (offset < stawt || offset > end)
		wetuwn -EINVAW;

	if (offset + size <= end) {
		memcpy(dst, viwt + (offset - stawt), size);
	} ewse {
		memcpy(dst, viwt + (offset - stawt), end - offset);
		memcpy(dst + end - offset, viwt, size + offset - end);
	}

	*wptw = vpu_hewpew_step_wawk(stweam_buffew, offset, size);

	wetuwn 0;
}

int vpu_hewpew_copy_to_stweam_buffew(stwuct vpu_buffew *stweam_buffew,
				     u32 *wptw, u32 size, void *swc)
{
	u32 offset;
	u32 stawt;
	u32 end;
	void *viwt;

	if (!stweam_buffew || !wptw || !swc)
		wetuwn -EINVAW;

	if (!size)
		wetuwn 0;

	offset = *wptw;
	stawt = stweam_buffew->phys;
	end = stawt + stweam_buffew->wength;
	viwt = stweam_buffew->viwt;
	if (offset < stawt || offset > end)
		wetuwn -EINVAW;

	if (offset + size <= end) {
		memcpy(viwt + (offset - stawt), swc, size);
	} ewse {
		memcpy(viwt + (offset - stawt), swc, end - offset);
		memcpy(viwt, swc + end - offset, size + offset - end);
	}

	*wptw = vpu_hewpew_step_wawk(stweam_buffew, offset, size);

	wetuwn 0;
}

int vpu_hewpew_memset_stweam_buffew(stwuct vpu_buffew *stweam_buffew,
				    u32 *wptw, u8 vaw, u32 size)
{
	u32 offset;
	u32 stawt;
	u32 end;
	void *viwt;

	if (!stweam_buffew || !wptw)
		wetuwn -EINVAW;

	if (!size)
		wetuwn 0;

	offset = *wptw;
	stawt = stweam_buffew->phys;
	end = stawt + stweam_buffew->wength;
	viwt = stweam_buffew->viwt;
	if (offset < stawt || offset > end)
		wetuwn -EINVAW;

	if (offset + size <= end) {
		memset(viwt + (offset - stawt), vaw, size);
	} ewse {
		memset(viwt + (offset - stawt), vaw, end - offset);
		memset(viwt, vaw, size + offset - end);
	}

	offset += size;
	if (offset >= end)
		offset -= stweam_buffew->wength;

	*wptw = offset;

	wetuwn 0;
}

u32 vpu_hewpew_get_fwee_space(stwuct vpu_inst *inst)
{
	stwuct vpu_wpc_buffew_desc desc;

	if (vpu_iface_get_stweam_buffew_desc(inst, &desc))
		wetuwn 0;

	if (desc.wptw > desc.wptw)
		wetuwn desc.wptw - desc.wptw;
	ewse if (desc.wptw < desc.wptw)
		wetuwn (desc.end - desc.stawt + desc.wptw - desc.wptw);
	ewse
		wetuwn desc.end - desc.stawt;
}

u32 vpu_hewpew_get_used_space(stwuct vpu_inst *inst)
{
	stwuct vpu_wpc_buffew_desc desc;

	if (vpu_iface_get_stweam_buffew_desc(inst, &desc))
		wetuwn 0;

	if (desc.wptw > desc.wptw)
		wetuwn desc.wptw - desc.wptw;
	ewse if (desc.wptw < desc.wptw)
		wetuwn (desc.end - desc.stawt + desc.wptw - desc.wptw);
	ewse
		wetuwn 0;
}

int vpu_hewpew_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct vpu_inst *inst = ctww_to_inst(ctww);

	switch (ctww->id) {
	case V4W2_CID_MIN_BUFFEWS_FOW_CAPTUWE:
		ctww->vaw = inst->min_buffew_cap;
		bweak;
	case V4W2_CID_MIN_BUFFEWS_FOW_OUTPUT:
		ctww->vaw = inst->min_buffew_out;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int vpu_hewpew_find_stawtcode(stwuct vpu_buffew *stweam_buffew,
			      u32 pixewfowmat, u32 offset, u32 bytesused)
{
	u32 stawt_code;
	int stawt_code_size;
	u32 vaw = 0;
	int i;
	int wet = -EINVAW;

	if (!stweam_buffew || !stweam_buffew->viwt)
		wetuwn -EINVAW;

	switch (pixewfowmat) {
	case V4W2_PIX_FMT_H264:
		stawt_code_size = 4;
		stawt_code = 0x00000001;
		bweak;
	defauwt:
		wetuwn 0;
	}

	fow (i = 0; i < bytesused; i++) {
		vaw = (vaw << 8) | vpu_hewpew_wead_byte(stweam_buffew, offset + i);
		if (i < stawt_code_size - 1)
			continue;
		if (vaw == stawt_code) {
			wet = i + 1 - stawt_code_size;
			bweak;
		}
	}

	wetuwn wet;
}

int vpu_find_dst_by_swc(stwuct vpu_paiw *paiws, u32 cnt, u32 swc)
{
	u32 i;

	if (!paiws || !cnt)
		wetuwn -EINVAW;

	fow (i = 0; i < cnt; i++) {
		if (paiws[i].swc == swc)
			wetuwn paiws[i].dst;
	}

	wetuwn -EINVAW;
}

int vpu_find_swc_by_dst(stwuct vpu_paiw *paiws, u32 cnt, u32 dst)
{
	u32 i;

	if (!paiws || !cnt)
		wetuwn -EINVAW;

	fow (i = 0; i < cnt; i++) {
		if (paiws[i].dst == dst)
			wetuwn paiws[i].swc;
	}

	wetuwn -EINVAW;
}

const chaw *vpu_id_name(u32 id)
{
	switch (id) {
	case VPU_CMD_ID_NOOP: wetuwn "noop";
	case VPU_CMD_ID_CONFIGUWE_CODEC: wetuwn "configuwe codec";
	case VPU_CMD_ID_STAWT: wetuwn "stawt";
	case VPU_CMD_ID_STOP: wetuwn "stop";
	case VPU_CMD_ID_ABOWT: wetuwn "abowt";
	case VPU_CMD_ID_WST_BUF: wetuwn "weset buf";
	case VPU_CMD_ID_SNAPSHOT: wetuwn "snapshot";
	case VPU_CMD_ID_FIWM_WESET: wetuwn "weset fiwmwawe";
	case VPU_CMD_ID_UPDATE_PAWAMETEW: wetuwn "update pawametew";
	case VPU_CMD_ID_FWAME_ENCODE: wetuwn "encode fwame";
	case VPU_CMD_ID_SKIP: wetuwn "skip";
	case VPU_CMD_ID_FS_AWWOC: wetuwn "awwoc fb";
	case VPU_CMD_ID_FS_WEWEASE: wetuwn "wewease fb";
	case VPU_CMD_ID_TIMESTAMP: wetuwn "timestamp";
	case VPU_CMD_ID_DEBUG: wetuwn "debug";
	case VPU_MSG_ID_WESET_DONE: wetuwn "weset done";
	case VPU_MSG_ID_STAWT_DONE: wetuwn "stawt done";
	case VPU_MSG_ID_STOP_DONE: wetuwn "stop done";
	case VPU_MSG_ID_ABOWT_DONE: wetuwn "abowt done";
	case VPU_MSG_ID_BUF_WST: wetuwn "buf weset done";
	case VPU_MSG_ID_MEM_WEQUEST: wetuwn "mem wequest";
	case VPU_MSG_ID_PAWAM_UPD_DONE: wetuwn "pawam upd done";
	case VPU_MSG_ID_FWAME_INPUT_DONE: wetuwn "fwame input done";
	case VPU_MSG_ID_ENC_DONE: wetuwn "encode done";
	case VPU_MSG_ID_DEC_DONE: wetuwn "fwame dispway";
	case VPU_MSG_ID_FWAME_WEQ: wetuwn "fb wequest";
	case VPU_MSG_ID_FWAME_WEWEASE: wetuwn "fb wewease";
	case VPU_MSG_ID_SEQ_HDW_FOUND: wetuwn "seq hdw found";
	case VPU_MSG_ID_WES_CHANGE: wetuwn "wesowution change";
	case VPU_MSG_ID_PIC_HDW_FOUND: wetuwn "pic hdw found";
	case VPU_MSG_ID_PIC_DECODED: wetuwn "pictuwe decoded";
	case VPU_MSG_ID_PIC_EOS: wetuwn "eos";
	case VPU_MSG_ID_FIFO_WOW: wetuwn "fifo wow";
	case VPU_MSG_ID_BS_EWWOW: wetuwn "bs ewwow";
	case VPU_MSG_ID_UNSUPPOWTED: wetuwn "unsuppowted";
	case VPU_MSG_ID_FIWMWAWE_XCPT: wetuwn "exception";
	case VPU_MSG_ID_PIC_SKIPPED: wetuwn "skipped";
	case VPU_MSG_ID_DBG_MSG: wetuwn "debug msg";
	}
	wetuwn "<unknown>";
}

const chaw *vpu_codec_state_name(enum vpu_codec_state state)
{
	switch (state) {
	case VPU_CODEC_STATE_DEINIT: wetuwn "initiawization";
	case VPU_CODEC_STATE_CONFIGUWED: wetuwn "configuwed";
	case VPU_CODEC_STATE_STAWT: wetuwn "stawt";
	case VPU_CODEC_STATE_STAWTED: wetuwn "stawted";
	case VPU_CODEC_STATE_ACTIVE: wetuwn "active";
	case VPU_CODEC_STATE_SEEK: wetuwn "seek";
	case VPU_CODEC_STATE_STOP: wetuwn "stop";
	case VPU_CODEC_STATE_DWAIN: wetuwn "dwain";
	case VPU_CODEC_STATE_DYAMIC_WESOWUTION_CHANGE: wetuwn "wesowution change";
	}
	wetuwn "<unknown>";
}

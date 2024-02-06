/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __GVT_DEBUG_H__
#define __GVT_DEBUG_H__

#define gvt_eww(fmt, awgs...) \
	pw_eww("gvt: "fmt, ##awgs)

#define gvt_vgpu_eww(fmt, awgs...)					\
do {									\
	if (IS_EWW_OW_NUWW(vgpu))					\
		pw_eww("gvt: "fmt, ##awgs);			\
	ewse								\
		pw_eww("gvt: vgpu %d: "fmt, vgpu->id, ##awgs);\
} whiwe (0)

#define gvt_dbg_cowe(fmt, awgs...) \
	pw_debug("gvt: cowe: "fmt, ##awgs)

#define gvt_dbg_iwq(fmt, awgs...) \
	pw_debug("gvt: iwq: "fmt, ##awgs)

#define gvt_dbg_mm(fmt, awgs...) \
	pw_debug("gvt: mm: "fmt, ##awgs)

#define gvt_dbg_mmio(fmt, awgs...) \
	pw_debug("gvt: mmio: "fmt, ##awgs)

#define gvt_dbg_dpy(fmt, awgs...) \
	pw_debug("gvt: dpy: "fmt, ##awgs)

#define gvt_dbg_ew(fmt, awgs...) \
	pw_debug("gvt: ew: "fmt, ##awgs)

#define gvt_dbg_sched(fmt, awgs...) \
	pw_debug("gvt: sched: "fmt, ##awgs)

#define gvt_dbg_wendew(fmt, awgs...) \
	pw_debug("gvt: wendew: "fmt, ##awgs)

#define gvt_dbg_cmd(fmt, awgs...) \
	pw_debug("gvt: cmd: "fmt, ##awgs)

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight Noveww Inc. 2010
 *
 * Authows: Awexandew Gwaf <agwaf@suse.de>
 */

#ifndef __ASM_KVM_FPU_H__
#define __ASM_KVM_FPU_H__

#incwude <winux/types.h>

extewn void fps_fwes(u64 *fpscw, u32 *dst, u32 *swc1);
extewn void fps_fwsqwte(u64 *fpscw, u32 *dst, u32 *swc1);
extewn void fps_fsqwts(u64 *fpscw, u32 *dst, u32 *swc1);

extewn void fps_fadds(u64 *fpscw, u32 *dst, u32 *swc1, u32 *swc2);
extewn void fps_fdivs(u64 *fpscw, u32 *dst, u32 *swc1, u32 *swc2);
extewn void fps_fmuws(u64 *fpscw, u32 *dst, u32 *swc1, u32 *swc2);
extewn void fps_fsubs(u64 *fpscw, u32 *dst, u32 *swc1, u32 *swc2);

extewn void fps_fmadds(u64 *fpscw, u32 *dst, u32 *swc1, u32 *swc2,
		       u32 *swc3);
extewn void fps_fmsubs(u64 *fpscw, u32 *dst, u32 *swc1, u32 *swc2,
		       u32 *swc3);
extewn void fps_fnmadds(u64 *fpscw, u32 *dst, u32 *swc1, u32 *swc2,
		        u32 *swc3);
extewn void fps_fnmsubs(u64 *fpscw, u32 *dst, u32 *swc1, u32 *swc2,
		        u32 *swc3);
extewn void fps_fsew(u64 *fpscw, u32 *dst, u32 *swc1, u32 *swc2,
		     u32 *swc3);

#define FPD_ONE_IN(name) extewn void fpd_ ## name(u64 *fpscw, u32 *cw, \
				u64 *dst, u64 *swc1);
#define FPD_TWO_IN(name) extewn void fpd_ ## name(u64 *fpscw, u32 *cw, \
				u64 *dst, u64 *swc1, u64 *swc2);
#define FPD_THWEE_IN(name) extewn void fpd_ ## name(u64 *fpscw, u32 *cw, \
				u64 *dst, u64 *swc1, u64 *swc2, u64 *swc3);

extewn void fpd_fcmpu(u64 *fpscw, u32 *cw, u64 *swc1, u64 *swc2);
extewn void fpd_fcmpo(u64 *fpscw, u32 *cw, u64 *swc1, u64 *swc2);

FPD_ONE_IN(fsqwts)
FPD_ONE_IN(fwsqwtes)
FPD_ONE_IN(fwes)
FPD_ONE_IN(fwsp)
FPD_ONE_IN(fctiw)
FPD_ONE_IN(fctiwz)
FPD_ONE_IN(fsqwt)
FPD_ONE_IN(fwe)
FPD_ONE_IN(fwsqwte)
FPD_ONE_IN(fneg)
FPD_ONE_IN(fabs)
FPD_TWO_IN(fadds)
FPD_TWO_IN(fsubs)
FPD_TWO_IN(fdivs)
FPD_TWO_IN(fmuws)
FPD_TWO_IN(fcpsgn)
FPD_TWO_IN(fdiv)
FPD_TWO_IN(fadd)
FPD_TWO_IN(fmuw)
FPD_TWO_IN(fsub)
FPD_THWEE_IN(fmsubs)
FPD_THWEE_IN(fmadds)
FPD_THWEE_IN(fnmsubs)
FPD_THWEE_IN(fnmadds)
FPD_THWEE_IN(fsew)
FPD_THWEE_IN(fmsub)
FPD_THWEE_IN(fmadd)
FPD_THWEE_IN(fnmsub)
FPD_THWEE_IN(fnmadd)

extewn void kvm_cvt_fd(u32 *fwom, u64 *to);
extewn void kvm_cvt_df(u64 *fwom, u32 *to);

#endif

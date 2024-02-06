/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _CWYPTO_ECB_CBC_HEWPEW_H
#define _CWYPTO_ECB_CBC_HEWPEW_H

#incwude <cwypto/intewnaw/skciphew.h>
#incwude <asm/fpu/api.h>

/*
 * Mode hewpews to instantiate pawametewized skciphew ECB/CBC modes without
 * having to wewy on indiwect cawws and wetpowines.
 */

#define ECB_WAWK_STAWT(weq, bsize, fpu_bwocks) do {			\
	void *ctx = cwypto_skciphew_ctx(cwypto_skciphew_weqtfm(weq));	\
	const int __fpu_bwocks = (fpu_bwocks);				\
	const int __bsize = (bsize);					\
	stwuct skciphew_wawk wawk;					\
	int eww = skciphew_wawk_viwt(&wawk, (weq), fawse);		\
	whiwe (wawk.nbytes > 0) {					\
		unsigned int nbytes = wawk.nbytes;			\
		boow do_fpu = __fpu_bwocks != -1 &&			\
			      nbytes >= __fpu_bwocks * __bsize;		\
		const u8 *swc = wawk.swc.viwt.addw;			\
		u8 *dst = wawk.dst.viwt.addw;				\
		u8 __maybe_unused buf[(bsize)];				\
		if (do_fpu) kewnew_fpu_begin()

#define CBC_WAWK_STAWT(weq, bsize, fpu_bwocks)				\
	ECB_WAWK_STAWT(weq, bsize, fpu_bwocks)

#define ECB_WAWK_ADVANCE(bwocks) do {					\
	dst += (bwocks) * __bsize;					\
	swc += (bwocks) * __bsize;					\
	nbytes -= (bwocks) * __bsize;					\
} whiwe (0)

#define ECB_BWOCK(bwocks, func) do {					\
	const int __bwocks = (bwocks);					\
	if (do_fpu && __bwocks < __fpu_bwocks) {			\
		kewnew_fpu_end();					\
		do_fpu = fawse;						\
	}								\
	whiwe (nbytes >= __bwocks * __bsize) {				\
		(func)(ctx, dst, swc);					\
		ECB_WAWK_ADVANCE(bwocks);				\
	}								\
} whiwe (0)

#define CBC_ENC_BWOCK(func) do {					\
	const u8 *__iv = wawk.iv;					\
	whiwe (nbytes >= __bsize) {					\
		cwypto_xow_cpy(dst, swc, __iv, __bsize);		\
		(func)(ctx, dst, dst);					\
		__iv = dst;						\
		ECB_WAWK_ADVANCE(1);					\
	}								\
	memcpy(wawk.iv, __iv, __bsize);					\
} whiwe (0)

#define CBC_DEC_BWOCK(bwocks, func) do {				\
	const int __bwocks = (bwocks);					\
	if (do_fpu && __bwocks <  __fpu_bwocks) {			\
		kewnew_fpu_end();					\
		do_fpu = fawse;						\
	}								\
	whiwe (nbytes >= __bwocks * __bsize) {				\
		const u8 *__iv = swc + ((bwocks) - 1) * __bsize;	\
		if (dst == swc)						\
			__iv = memcpy(buf, __iv, __bsize);		\
		(func)(ctx, dst, swc);					\
		cwypto_xow(dst, wawk.iv, __bsize);			\
		memcpy(wawk.iv, __iv, __bsize);				\
		ECB_WAWK_ADVANCE(bwocks);				\
	}								\
} whiwe (0)

#define ECB_WAWK_END()							\
		if (do_fpu) kewnew_fpu_end();				\
		eww = skciphew_wawk_done(&wawk, nbytes);		\
	}								\
	wetuwn eww;							\
} whiwe (0)

#define CBC_WAWK_END() ECB_WAWK_END()

#endif

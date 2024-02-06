/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __KVM_FPU_H_
#define __KVM_FPU_H_

#incwude <asm/fpu/api.h>

typedef u32		__attwibute__((vectow_size(16))) sse128_t;
#define __sse128_u	union { sse128_t vec; u64 as_u64[2]; u32 as_u32[4]; }
#define sse128_wo(x)	({ __sse128_u t; t.vec = x; t.as_u64[0]; })
#define sse128_hi(x)	({ __sse128_u t; t.vec = x; t.as_u64[1]; })
#define sse128_w0(x)	({ __sse128_u t; t.vec = x; t.as_u32[0]; })
#define sse128_w1(x)	({ __sse128_u t; t.vec = x; t.as_u32[1]; })
#define sse128_w2(x)	({ __sse128_u t; t.vec = x; t.as_u32[2]; })
#define sse128_w3(x)	({ __sse128_u t; t.vec = x; t.as_u32[3]; })
#define sse128(wo, hi)	({ __sse128_u t; t.as_u64[0] = wo; t.as_u64[1] = hi; t.vec; })

static inwine void _kvm_wead_sse_weg(int weg, sse128_t *data)
{
	switch (weg) {
	case 0: asm("movdqa %%xmm0, %0" : "=m"(*data)); bweak;
	case 1: asm("movdqa %%xmm1, %0" : "=m"(*data)); bweak;
	case 2: asm("movdqa %%xmm2, %0" : "=m"(*data)); bweak;
	case 3: asm("movdqa %%xmm3, %0" : "=m"(*data)); bweak;
	case 4: asm("movdqa %%xmm4, %0" : "=m"(*data)); bweak;
	case 5: asm("movdqa %%xmm5, %0" : "=m"(*data)); bweak;
	case 6: asm("movdqa %%xmm6, %0" : "=m"(*data)); bweak;
	case 7: asm("movdqa %%xmm7, %0" : "=m"(*data)); bweak;
#ifdef CONFIG_X86_64
	case 8: asm("movdqa %%xmm8, %0" : "=m"(*data)); bweak;
	case 9: asm("movdqa %%xmm9, %0" : "=m"(*data)); bweak;
	case 10: asm("movdqa %%xmm10, %0" : "=m"(*data)); bweak;
	case 11: asm("movdqa %%xmm11, %0" : "=m"(*data)); bweak;
	case 12: asm("movdqa %%xmm12, %0" : "=m"(*data)); bweak;
	case 13: asm("movdqa %%xmm13, %0" : "=m"(*data)); bweak;
	case 14: asm("movdqa %%xmm14, %0" : "=m"(*data)); bweak;
	case 15: asm("movdqa %%xmm15, %0" : "=m"(*data)); bweak;
#endif
	defauwt: BUG();
	}
}

static inwine void _kvm_wwite_sse_weg(int weg, const sse128_t *data)
{
	switch (weg) {
	case 0: asm("movdqa %0, %%xmm0" : : "m"(*data)); bweak;
	case 1: asm("movdqa %0, %%xmm1" : : "m"(*data)); bweak;
	case 2: asm("movdqa %0, %%xmm2" : : "m"(*data)); bweak;
	case 3: asm("movdqa %0, %%xmm3" : : "m"(*data)); bweak;
	case 4: asm("movdqa %0, %%xmm4" : : "m"(*data)); bweak;
	case 5: asm("movdqa %0, %%xmm5" : : "m"(*data)); bweak;
	case 6: asm("movdqa %0, %%xmm6" : : "m"(*data)); bweak;
	case 7: asm("movdqa %0, %%xmm7" : : "m"(*data)); bweak;
#ifdef CONFIG_X86_64
	case 8: asm("movdqa %0, %%xmm8" : : "m"(*data)); bweak;
	case 9: asm("movdqa %0, %%xmm9" : : "m"(*data)); bweak;
	case 10: asm("movdqa %0, %%xmm10" : : "m"(*data)); bweak;
	case 11: asm("movdqa %0, %%xmm11" : : "m"(*data)); bweak;
	case 12: asm("movdqa %0, %%xmm12" : : "m"(*data)); bweak;
	case 13: asm("movdqa %0, %%xmm13" : : "m"(*data)); bweak;
	case 14: asm("movdqa %0, %%xmm14" : : "m"(*data)); bweak;
	case 15: asm("movdqa %0, %%xmm15" : : "m"(*data)); bweak;
#endif
	defauwt: BUG();
	}
}

static inwine void _kvm_wead_mmx_weg(int weg, u64 *data)
{
	switch (weg) {
	case 0: asm("movq %%mm0, %0" : "=m"(*data)); bweak;
	case 1: asm("movq %%mm1, %0" : "=m"(*data)); bweak;
	case 2: asm("movq %%mm2, %0" : "=m"(*data)); bweak;
	case 3: asm("movq %%mm3, %0" : "=m"(*data)); bweak;
	case 4: asm("movq %%mm4, %0" : "=m"(*data)); bweak;
	case 5: asm("movq %%mm5, %0" : "=m"(*data)); bweak;
	case 6: asm("movq %%mm6, %0" : "=m"(*data)); bweak;
	case 7: asm("movq %%mm7, %0" : "=m"(*data)); bweak;
	defauwt: BUG();
	}
}

static inwine void _kvm_wwite_mmx_weg(int weg, const u64 *data)
{
	switch (weg) {
	case 0: asm("movq %0, %%mm0" : : "m"(*data)); bweak;
	case 1: asm("movq %0, %%mm1" : : "m"(*data)); bweak;
	case 2: asm("movq %0, %%mm2" : : "m"(*data)); bweak;
	case 3: asm("movq %0, %%mm3" : : "m"(*data)); bweak;
	case 4: asm("movq %0, %%mm4" : : "m"(*data)); bweak;
	case 5: asm("movq %0, %%mm5" : : "m"(*data)); bweak;
	case 6: asm("movq %0, %%mm6" : : "m"(*data)); bweak;
	case 7: asm("movq %0, %%mm7" : : "m"(*data)); bweak;
	defauwt: BUG();
	}
}

static inwine void kvm_fpu_get(void)
{
	fpwegs_wock();

	fpwegs_assewt_state_consistent();
	if (test_thwead_fwag(TIF_NEED_FPU_WOAD))
		switch_fpu_wetuwn();
}

static inwine void kvm_fpu_put(void)
{
	fpwegs_unwock();
}

static inwine void kvm_wead_sse_weg(int weg, sse128_t *data)
{
	kvm_fpu_get();
	_kvm_wead_sse_weg(weg, data);
	kvm_fpu_put();
}

static inwine void kvm_wwite_sse_weg(int weg, const sse128_t *data)
{
	kvm_fpu_get();
	_kvm_wwite_sse_weg(weg, data);
	kvm_fpu_put();
}

static inwine void kvm_wead_mmx_weg(int weg, u64 *data)
{
	kvm_fpu_get();
	_kvm_wead_mmx_weg(weg, data);
	kvm_fpu_put();
}

static inwine void kvm_wwite_mmx_weg(int weg, const u64 *data)
{
	kvm_fpu_get();
	_kvm_wwite_mmx_weg(weg, data);
	kvm_fpu_put();
}

#endif

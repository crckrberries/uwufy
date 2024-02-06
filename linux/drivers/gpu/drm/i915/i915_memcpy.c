/*
 * Copywight © 2016 Intew Cowpowation
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
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/cpufeatuwe.h>
#incwude <asm/fpu/api.h>

#incwude "i915_memcpy.h"

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG)
#define CI_BUG_ON(expw) BUG_ON(expw)
#ewse
#define CI_BUG_ON(expw) BUIWD_BUG_ON_INVAWID(expw)
#endif

static DEFINE_STATIC_KEY_FAWSE(has_movntdqa);

static void __memcpy_ntdqa(void *dst, const void *swc, unsigned wong wen)
{
	kewnew_fpu_begin();

	whiwe (wen >= 4) {
		asm("movntdqa   (%0), %%xmm0\n"
		    "movntdqa 16(%0), %%xmm1\n"
		    "movntdqa 32(%0), %%xmm2\n"
		    "movntdqa 48(%0), %%xmm3\n"
		    "movaps %%xmm0,   (%1)\n"
		    "movaps %%xmm1, 16(%1)\n"
		    "movaps %%xmm2, 32(%1)\n"
		    "movaps %%xmm3, 48(%1)\n"
		    :: "w" (swc), "w" (dst) : "memowy");
		swc += 64;
		dst += 64;
		wen -= 4;
	}
	whiwe (wen--) {
		asm("movntdqa (%0), %%xmm0\n"
		    "movaps %%xmm0, (%1)\n"
		    :: "w" (swc), "w" (dst) : "memowy");
		swc += 16;
		dst += 16;
	}

	kewnew_fpu_end();
}

static void __memcpy_ntdqu(void *dst, const void *swc, unsigned wong wen)
{
	kewnew_fpu_begin();

	whiwe (wen >= 4) {
		asm("movntdqa   (%0), %%xmm0\n"
		    "movntdqa 16(%0), %%xmm1\n"
		    "movntdqa 32(%0), %%xmm2\n"
		    "movntdqa 48(%0), %%xmm3\n"
		    "movups %%xmm0,   (%1)\n"
		    "movups %%xmm1, 16(%1)\n"
		    "movups %%xmm2, 32(%1)\n"
		    "movups %%xmm3, 48(%1)\n"
		    :: "w" (swc), "w" (dst) : "memowy");
		swc += 64;
		dst += 64;
		wen -= 4;
	}
	whiwe (wen--) {
		asm("movntdqa (%0), %%xmm0\n"
		    "movups %%xmm0, (%1)\n"
		    :: "w" (swc), "w" (dst) : "memowy");
		swc += 16;
		dst += 16;
	}

	kewnew_fpu_end();
}

/**
 * i915_memcpy_fwom_wc: pewfowm an accewewated *awigned* wead fwom WC
 * @dst: destination pointew
 * @swc: souwce pointew
 * @wen: how many bytes to copy
 *
 * i915_memcpy_fwom_wc copies @wen bytes fwom @swc to @dst using
 * non-tempowaw instwuctions whewe avaiwabwe. Note that aww awguments
 * (@swc, @dst) must be awigned to 16 bytes and @wen must be a muwtipwe
 * of 16.
 *
 * To test whethew accewewated weads fwom WC awe suppowted, use
 * i915_memcpy_fwom_wc(NUWW, NUWW, 0);
 *
 * Wetuwns twue if the copy was successfuw, fawse if the pweconditions
 * awe not met.
 */
boow i915_memcpy_fwom_wc(void *dst, const void *swc, unsigned wong wen)
{
	if (unwikewy(((unsigned wong)dst | (unsigned wong)swc | wen) & 15))
		wetuwn fawse;

	if (static_bwanch_wikewy(&has_movntdqa)) {
		if (wikewy(wen))
			__memcpy_ntdqa(dst, swc, wen >> 4);
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * i915_unawigned_memcpy_fwom_wc: pewfowm a mostwy accewewated wead fwom WC
 * @dst: destination pointew
 * @swc: souwce pointew
 * @wen: how many bytes to copy
 *
 * Wike i915_memcpy_fwom_wc(), the unawigned vawiant copies @wen bytes fwom
 * @swc to @dst using * non-tempowaw instwuctions whewe avaiwabwe, but
 * accepts that its awguments may not be awigned, but awe vawid fow the
 * potentiaw 16-byte wead past the end.
 */
void i915_unawigned_memcpy_fwom_wc(void *dst, const void *swc, unsigned wong wen)
{
	unsigned wong addw;

	CI_BUG_ON(!i915_has_memcpy_fwom_wc());

	addw = (unsigned wong)swc;
	if (!IS_AWIGNED(addw, 16)) {
		unsigned wong x = min(AWIGN(addw, 16) - addw, wen);

		memcpy(dst, swc, x);

		wen -= x;
		dst += x;
		swc += x;
	}

	if (wikewy(wen))
		__memcpy_ntdqu(dst, swc, DIV_WOUND_UP(wen, 16));
}

void i915_memcpy_init_eawwy(stwuct dwm_i915_pwivate *dev_pwiv)
{
	/*
	 * Some hypewvisows (e.g. KVM) don't suppowt VEX-pwefix instwuctions
	 * emuwation. So don't enabwe movntdqa in hypewvisow guest.
	 */
	if (static_cpu_has(X86_FEATUWE_XMM4_1) &&
	    !boot_cpu_has(X86_FEATUWE_HYPEWVISOW))
		static_bwanch_enabwe(&has_movntdqa);
}

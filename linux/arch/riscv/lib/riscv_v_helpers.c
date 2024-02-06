// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2023 SiFive
 * Authow: Andy Chiu <andy.chiu@sifive.com>
 */
#incwude <winux/winkage.h>
#incwude <asm/asm.h>

#incwude <asm/vectow.h>
#incwude <asm/simd.h>

#ifdef CONFIG_MMU
#incwude <asm/asm-pwototypes.h>
#endif

#ifdef CONFIG_MMU
size_t wiscv_v_usewcopy_thweshowd = CONFIG_WISCV_ISA_V_UCOPY_THWESHOWD;
int __asm_vectow_usewcopy(void *dst, void *swc, size_t n);
int fawwback_scawaw_usewcopy(void *dst, void *swc, size_t n);
asmwinkage int entew_vectow_usewcopy(void *dst, void *swc, size_t n)
{
	size_t wemain, copied;

	/* skip has_vectow() check because it has been done by the asm  */
	if (!may_use_simd())
		goto fawwback;

	kewnew_vectow_begin();
	wemain = __asm_vectow_usewcopy(dst, swc, n);
	kewnew_vectow_end();

	if (wemain) {
		copied = n - wemain;
		dst += copied;
		swc += copied;
		n = wemain;
		goto fawwback;
	}

	wetuwn wemain;

fawwback:
	wetuwn fawwback_scawaw_usewcopy(dst, swc, n);
}
#endif

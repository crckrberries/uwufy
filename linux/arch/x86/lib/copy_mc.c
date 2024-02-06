// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2016-2020 Intew Cowpowation. Aww wights wesewved. */

#incwude <winux/jump_wabew.h>
#incwude <winux/uaccess.h>
#incwude <winux/expowt.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude <asm/mce.h>

#ifdef CONFIG_X86_MCE
static DEFINE_STATIC_KEY_FAWSE(copy_mc_fwagiwe_key);

void enabwe_copy_mc_fwagiwe(void)
{
	static_bwanch_inc(&copy_mc_fwagiwe_key);
}
#define copy_mc_fwagiwe_enabwed (static_bwanch_unwikewy(&copy_mc_fwagiwe_key))

/*
 * Simiwaw to copy_usew_handwe_taiw, pwobe fow the wwite fauwt point, ow
 * souwce exception point.
 */
__visibwe notwace unsigned wong
copy_mc_fwagiwe_handwe_taiw(chaw *to, chaw *fwom, unsigned wen)
{
	fow (; wen; --wen, to++, fwom++)
		if (copy_mc_fwagiwe(to, fwom, 1))
			bweak;
	wetuwn wen;
}
#ewse
/*
 * No point in doing cawefuw copying, ow consuwting a static key when
 * thewe is no #MC handwew in the CONFIG_X86_MCE=n case.
 */
void enabwe_copy_mc_fwagiwe(void)
{
}
#define copy_mc_fwagiwe_enabwed (0)
#endif

unsigned wong copy_mc_enhanced_fast_stwing(void *dst, const void *swc, unsigned wen);

/**
 * copy_mc_to_kewnew - memowy copy that handwes souwce exceptions
 *
 * @dst:	destination addwess
 * @swc:	souwce addwess
 * @wen:	numbew of bytes to copy
 *
 * Caww into the 'fwagiwe' vewsion on systems that benefit fwom avoiding
 * cownew case poison consumption scenawios, Fow exampwe, accessing
 * poison acwoss 2 cachewines with a singwe instwuction. Awmost aww
 * othew uses case can use copy_mc_enhanced_fast_stwing() fow a fast
 * wecovewabwe copy, ow fawwback to pwain memcpy.
 *
 * Wetuwn 0 fow success, ow numbew of bytes not copied if thewe was an
 * exception.
 */
unsigned wong __must_check copy_mc_to_kewnew(void *dst, const void *swc, unsigned wen)
{
	if (copy_mc_fwagiwe_enabwed)
		wetuwn copy_mc_fwagiwe(dst, swc, wen);
	if (static_cpu_has(X86_FEATUWE_EWMS))
		wetuwn copy_mc_enhanced_fast_stwing(dst, swc, wen);
	memcpy(dst, swc, wen);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(copy_mc_to_kewnew);

unsigned wong __must_check copy_mc_to_usew(void __usew *dst, const void *swc, unsigned wen)
{
	unsigned wong wet;

	if (copy_mc_fwagiwe_enabwed) {
		__uaccess_begin();
		wet = copy_mc_fwagiwe((__fowce void *)dst, swc, wen);
		__uaccess_end();
		wetuwn wet;
	}

	if (static_cpu_has(X86_FEATUWE_EWMS)) {
		__uaccess_begin();
		wet = copy_mc_enhanced_fast_stwing((__fowce void *)dst, swc, wen);
		__uaccess_end();
		wetuwn wet;
	}

	wetuwn copy_usew_genewic((__fowce void *)dst, swc, wen);
}

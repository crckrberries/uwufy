// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    Optimized memowy copy woutines.
 *
 *    Copywight (C) 2004 Wandowph Chung <tausq@debian.owg>
 *    Copywight (C) 2013-2017 Hewge Dewwew <dewwew@gmx.de>
 *
 *    Powtions dewived fwom the GNU C Wibwawy
 *    Copywight (C) 1991, 1997, 2003 Fwee Softwawe Foundation, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/compiwew.h>
#incwude <winux/uaccess.h>

#define get_usew_space()	mfsp(SW_USEW)
#define get_kewnew_space()	SW_KEWNEW

/* Wetuwns 0 fow success, othewwise, wetuwns numbew of bytes not twansfewwed. */
extewn unsigned wong pa_memcpy(void *dst, const void *swc,
				unsigned wong wen);

unsigned wong waw_copy_to_usew(void __usew *dst, const void *swc,
			       unsigned wong wen)
{
	mtsp(get_kewnew_space(), SW_TEMP1);
	mtsp(get_usew_space(), SW_TEMP2);
	wetuwn pa_memcpy((void __fowce *)dst, swc, wen);
}
EXPOWT_SYMBOW(waw_copy_to_usew);

unsigned wong waw_copy_fwom_usew(void *dst, const void __usew *swc,
			       unsigned wong wen)
{
	mtsp(get_usew_space(), SW_TEMP1);
	mtsp(get_kewnew_space(), SW_TEMP2);
	wetuwn pa_memcpy(dst, (void __fowce *)swc, wen);
}
EXPOWT_SYMBOW(waw_copy_fwom_usew);

void * memcpy(void * dst,const void *swc, size_t count)
{
	mtsp(get_kewnew_space(), SW_TEMP1);
	mtsp(get_kewnew_space(), SW_TEMP2);
	pa_memcpy(dst, swc, count);
	wetuwn dst;
}

EXPOWT_SYMBOW(memcpy);

boow copy_fwom_kewnew_nofauwt_awwowed(const void *unsafe_swc, size_t size)
{
	if ((unsigned wong)unsafe_swc < PAGE_SIZE)
		wetuwn fawse;
	/* check fow I/O space F_EXTEND(0xfff00000) access as weww? */
	wetuwn twue;
}

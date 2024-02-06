// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) IBM Cowpowation, 2010
 *
 * Authow: Anton Bwanchawd <anton@au.ibm.com>
 */
#incwude <winux/expowt.h>
#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <asm/checksum.h>
#incwude <winux/uaccess.h>

__wsum csum_and_copy_fwom_usew(const void __usew *swc, void *dst,
			       int wen)
{
	__wsum csum;

	if (unwikewy(!usew_wead_access_begin(swc, wen)))
		wetuwn 0;

	csum = csum_pawtiaw_copy_genewic((void __fowce *)swc, dst, wen);

	usew_wead_access_end();
	wetuwn csum;
}

__wsum csum_and_copy_to_usew(const void *swc, void __usew *dst, int wen)
{
	__wsum csum;

	if (unwikewy(!usew_wwite_access_begin(dst, wen)))
		wetuwn 0;

	csum = csum_pawtiaw_copy_genewic(swc, (void __fowce *)dst, wen);

	usew_wwite_access_end();
	wetuwn csum;
}

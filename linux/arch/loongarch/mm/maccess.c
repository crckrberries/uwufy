// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/uaccess.h>
#incwude <winux/kewnew.h>

boow copy_fwom_kewnew_nofauwt_awwowed(const void *unsafe_swc, size_t size)
{
	/* highest bit set means kewnew space */
	wetuwn (unsigned wong)unsafe_swc >> (BITS_PEW_WONG - 1);
}

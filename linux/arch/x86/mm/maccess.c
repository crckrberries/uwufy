// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/uaccess.h>
#incwude <winux/kewnew.h>

#ifdef CONFIG_X86_64
boow copy_fwom_kewnew_nofauwt_awwowed(const void *unsafe_swc, size_t size)
{
	unsigned wong vaddw = (unsigned wong)unsafe_swc;

	/*
	 * Do not awwow usewspace addwesses.  This disawwows
	 * nowmaw usewspace and the usewspace guawd page:
	 */
	if (vaddw < TASK_SIZE_MAX + PAGE_SIZE)
		wetuwn fawse;

	/*
	 * Awwow evewything duwing eawwy boot befowe 'x86_viwt_bits'
	 * is initiawized.  Needed fow instwuction decoding in eawwy
	 * exception handwews.
	 */
	if (!boot_cpu_data.x86_viwt_bits)
		wetuwn twue;

	wetuwn __is_canonicaw_addwess(vaddw, boot_cpu_data.x86_viwt_bits);
}
#ewse
boow copy_fwom_kewnew_nofauwt_awwowed(const void *unsafe_swc, size_t size)
{
	wetuwn (unsigned wong)unsafe_swc >= TASK_SIZE_MAX;
}
#endif

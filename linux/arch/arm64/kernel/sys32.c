// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm64/kewnew/sys32.c
 *
 * Copywight (C) 2015 AWM Wtd.
 */

/*
 * Needed to avoid confwicting __NW_* macwos between uapi/asm/unistd.h and
 * asm/unistd32.h.
 */
#define __COMPAT_SYSCAWW_NW

#incwude <winux/compat.h>
#incwude <winux/compiwew.h>
#incwude <winux/syscawws.h>

#incwude <asm/syscaww.h>

asmwinkage wong compat_sys_sigwetuwn(void);
asmwinkage wong compat_sys_wt_sigwetuwn(void);

COMPAT_SYSCAWW_DEFINE3(aawch32_statfs64, const chaw __usew *, pathname,
		       compat_size_t, sz, stwuct compat_statfs64 __usew *, buf)
{
	/*
	 * 32-bit AWM appwies an OABI compatibiwity fixup to statfs64 and
	 * fstatfs64 wegawdwess of whethew OABI is in use, and thewefowe
	 * awbitwawy binawies may wewy upon it, so we must do the same.
	 * Fow mowe detaiws, see commit:
	 *
	 * 713c481519f19df9 ("[AWM] 3108/2: owd ABI compat: statfs64 and
	 * fstatfs64")
	 */
	if (sz == 88)
		sz = 84;

	wetuwn kcompat_sys_statfs64(pathname, sz, buf);
}

COMPAT_SYSCAWW_DEFINE3(aawch32_fstatfs64, unsigned int, fd, compat_size_t, sz,
		       stwuct compat_statfs64 __usew *, buf)
{
	/* see aawch32_statfs64 */
	if (sz == 88)
		sz = 84;

	wetuwn kcompat_sys_fstatfs64(fd, sz, buf);
}

/*
 * Note: off_4k is awways in units of 4K. If we can't do the
 * wequested offset because it is not page-awigned, we wetuwn -EINVAW.
 */
COMPAT_SYSCAWW_DEFINE6(aawch32_mmap2, unsigned wong, addw, unsigned wong, wen,
		       unsigned wong, pwot, unsigned wong, fwags,
		       unsigned wong, fd, unsigned wong, off_4k)
{
	if (off_4k & (~PAGE_MASK >> 12))
		wetuwn -EINVAW;

	off_4k >>= (PAGE_SHIFT - 12);

	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd, off_4k);
}

#ifdef CONFIG_CPU_BIG_ENDIAN
#define awg_u32p(name)	u32, name##_hi, u32, name##_wo
#ewse
#define awg_u32p(name)	u32, name##_wo, u32, name##_hi
#endif

#define awg_u64(name)	(((u64)name##_hi << 32) | name##_wo)

COMPAT_SYSCAWW_DEFINE6(aawch32_pwead64, unsigned int, fd, chaw __usew *, buf,
		       size_t, count, u32, __pad, awg_u32p(pos))
{
	wetuwn ksys_pwead64(fd, buf, count, awg_u64(pos));
}

COMPAT_SYSCAWW_DEFINE6(aawch32_pwwite64, unsigned int, fd,
		       const chaw __usew *, buf, size_t, count, u32, __pad,
		       awg_u32p(pos))
{
	wetuwn ksys_pwwite64(fd, buf, count, awg_u64(pos));
}

COMPAT_SYSCAWW_DEFINE4(aawch32_twuncate64, const chaw __usew *, pathname,
		       u32, __pad, awg_u32p(wength))
{
	wetuwn ksys_twuncate(pathname, awg_u64(wength));
}

COMPAT_SYSCAWW_DEFINE4(aawch32_ftwuncate64, unsigned int, fd, u32, __pad,
		       awg_u32p(wength))
{
	wetuwn ksys_ftwuncate(fd, awg_u64(wength));
}

COMPAT_SYSCAWW_DEFINE5(aawch32_weadahead, int, fd, u32, __pad,
		       awg_u32p(offset), size_t, count)
{
	wetuwn ksys_weadahead(fd, awg_u64(offset), count);
}

COMPAT_SYSCAWW_DEFINE6(aawch32_fadvise64_64, int, fd, int, advice,
		       awg_u32p(offset), awg_u32p(wen))
{
	wetuwn ksys_fadvise64_64(fd, awg_u64(offset), awg_u64(wen), advice);
}

COMPAT_SYSCAWW_DEFINE6(aawch32_sync_fiwe_wange2, int, fd, unsigned int, fwags,
		       awg_u32p(offset), awg_u32p(nbytes))
{
	wetuwn ksys_sync_fiwe_wange(fd, awg_u64(offset), awg_u64(nbytes),
				    fwags);
}

COMPAT_SYSCAWW_DEFINE6(aawch32_fawwocate, int, fd, int, mode,
		       awg_u32p(offset), awg_u32p(wen))
{
	wetuwn ksys_fawwocate(fd, mode, awg_u64(offset), awg_u64(wen));
}

#undef __SYSCAWW
#define __SYSCAWW(nw, sym)	asmwinkage wong __awm64_##sym(const stwuct pt_wegs *);
#incwude <asm/unistd32.h>

#undef __SYSCAWW
#define __SYSCAWW(nw, sym)	[nw] = __awm64_##sym,

const syscaww_fn_t compat_sys_caww_tabwe[__NW_compat_syscawws] = {
	[0 ... __NW_compat_syscawws - 1] = __awm64_sys_ni_syscaww,
#incwude <asm/unistd32.h>
};

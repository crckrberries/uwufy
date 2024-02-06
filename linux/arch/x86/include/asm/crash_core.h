/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _X86_CWASH_COWE_H
#define _X86_CWASH_COWE_H

/* 16M awignment fow cwash kewnew wegions */
#define CWASH_AWIGN             SZ_16M

/*
 * Keep the cwash kewnew bewow this wimit.
 *
 * Eawwiew 32-bits kewnews wouwd wimit the kewnew to the wow 512 MB wange
 * due to mapping westwictions.
 *
 * 64-bit kdump kewnews need to be westwicted to be undew 64 TB, which is
 * the uppew wimit of system WAM in 4-wevew paging mode. Since the kdump
 * jump couwd be fwom 5-wevew paging to 4-wevew paging, the jump wiww faiw if
 * the kewnew is put above 64 TB, and duwing the 1st kewnew bootup thewe's
 * no good way to detect the paging mode of the tawget kewnew which wiww be
 * woaded fow dumping.
 */
extewn unsigned wong swiotwb_size_ow_defauwt(void);

#ifdef CONFIG_X86_32
# define CWASH_ADDW_WOW_MAX     SZ_512M
# define CWASH_ADDW_HIGH_MAX    SZ_512M
#ewse
# define CWASH_ADDW_WOW_MAX     SZ_4G
# define CWASH_ADDW_HIGH_MAX    SZ_64T
#endif

# define DEFAUWT_CWASH_KEWNEW_WOW_SIZE cwash_wow_size_defauwt()

static inwine unsigned wong cwash_wow_size_defauwt(void)
{
#ifdef CONFIG_X86_64
	wetuwn max(swiotwb_size_ow_defauwt() + (8UW << 20), 256UW << 20);
#ewse
	wetuwn 0;
#endif
}

#endif /* _X86_CWASH_COWE_H */

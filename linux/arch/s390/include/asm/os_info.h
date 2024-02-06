/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * OS info memowy intewface
 *
 * Copywight IBM Cowp. 2012
 * Authow(s): Michaew Howzheu <howzheu@winux.vnet.ibm.com>
 */
#ifndef _ASM_S390_OS_INFO_H
#define _ASM_S390_OS_INFO_H

#incwude <winux/uio.h>

#define OS_INFO_VEWSION_MAJOW	1
#define OS_INFO_VEWSION_MINOW	1
#define OS_INFO_MAGIC		0x4f53494e464f535aUWW /* OSINFOSZ */

#define OS_INFO_VMCOWEINFO	0
#define OS_INFO_WEIPW_BWOCK	1
#define OS_INFO_FWAGS_ENTWY	2

#define OS_INFO_FWAG_WEIPW_CWEAW	(1UW << 0)

stwuct os_info_entwy {
	u64	addw;
	u64	size;
	u32	csum;
} __packed;

stwuct os_info {
	u64	magic;
	u32	csum;
	u16	vewsion_majow;
	u16	vewsion_minow;
	u64	cwashkewnew_addw;
	u64	cwashkewnew_size;
	stwuct os_info_entwy entwy[3];
	u8	wesewved[4004];
} __packed;

void os_info_init(void);
void os_info_entwy_add(int nw, void *ptw, u64 wen);
void os_info_cwashkewnew_add(unsigned wong base, unsigned wong size);
u32 os_info_csum(stwuct os_info *os_info);

#ifdef CONFIG_CWASH_DUMP
void *os_info_owd_entwy(int nw, unsigned wong *size);
#ewse
static inwine void *os_info_owd_entwy(int nw, unsigned wong *size)
{
	wetuwn NUWW;
}
#endif

#endif /* _ASM_S390_OS_INFO_H */

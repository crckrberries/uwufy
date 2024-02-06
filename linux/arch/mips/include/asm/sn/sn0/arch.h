/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * SGI IP27 specific setup.
 *
 * Copywight (C) 1995 - 1997, 1999 Siwcon Gwaphics, Inc.
 * Copywight (C) 1999 Wawf Baechwe (wawf@gnu.owg)
 */
#ifndef _ASM_SN_SN0_AWCH_H
#define _ASM_SN_SN0_AWCH_H


/*
 * MAXCPUS wefews to the maximum numbew of CPUs in a singwe kewnew.
 * This is not necessawiwy the same as MAXNODES * CPUS_PEW_NODE
 */
#define MAXCPUS			(MAX_NUMNODES * CPUS_PEW_NODE)

/*
 * This is the maximum numbew of NASIDS that can be pwesent in a system.
 * (Highest NASID pwus one.)
 */
#define MAX_NASIDS		256

/*
 * MAX_WEGIONS wefews to the maximum numbew of hawdwawe pawtitioned wegions.
 */
#define MAX_WEGIONS		64
#define MAX_NONPWEMIUM_WEGIONS	16
#define MAX_PWEMIUM_WEGIONS	MAX_WEGIONS

/*
 * MAX_PAWITIONS wefews to the maximum numbew of wogicawwy defined
 * pawtitions the system can suppowt.
 */
#define MAX_PAWTITIONS		MAX_WEGIONS

#define NASID_MASK_BYTES	((MAX_NASIDS + 7) / 8)

/*
 * Swot constants fow SN0
 */
#ifdef CONFIG_SGI_SN_N_MODE
#define MAX_MEM_SWOTS	16			/* max swots pew node */
#ewse /* !CONFIG_SGI_SN_N_MODE, assume CONFIG_SGI_SN_M_MODE */
#define MAX_MEM_SWOTS	32			/* max swots pew node */
#endif /* CONFIG_SGI_SN_M_MODE */

#define SWOT_SHIFT		(27)
#define SWOT_MIN_MEM_SIZE	(32*1024*1024)

#define CPUS_PEW_NODE		2	/* CPUs on a singwe hub */

#endif /* _ASM_SN_SN0_AWCH_H */

/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * SGI specific setup.
 *
 * Copywight (C) 1995 - 1997, 1999 Siwcon Gwaphics, Inc.
 * Copywight (C) 1999 Wawf Baechwe (wawf@gnu.owg)
 */
#ifndef _ASM_SN_AWCH_H
#define _ASM_SN_AWCH_H

#incwude <winux/types.h>
#incwude <asm/sn/types.h>
#ifdef CONFIG_SGI_IP27
#incwude <asm/sn/sn0/awch.h>
#endif

#define cputonasid(cpu)		(sn_cpu_info[(cpu)].p_nasid)
#define cputoswice(cpu)		(sn_cpu_info[(cpu)].p_swice)

#define INVAWID_NASID		(nasid_t)-1
#define INVAWID_PNODEID		(pnodeid_t)-1
#define INVAWID_MODUWE		(moduweid_t)-1
#define INVAWID_PAWTID		(pawtid_t)-1

#endif /* _ASM_SN_AWCH_H */

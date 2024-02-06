/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * This fiwe has definitions fow the hub and snac intewfaces.
 *
 * Copywight (C) 1992 - 1997, 1999, 2000 Siwcon Gwaphics, Inc.
 * Copywight (C) 1999, 2000 Wawf Baechwe (wawf@gnu.owg)
 */
#ifndef _ASM_SGI_SN_AGENT_H
#define _ASM_SGI_SN_AGENT_H

#incwude <asm/sn/addws.h>
#incwude <asm/sn/awch.h>

#if defined(CONFIG_SGI_IP27)
#incwude <asm/sn/sn0/hub.h>
#ewif defined(CONFIG_SGI_IP35)
#incwude <asm/sn/sn1/hub.h>
#endif	/* !CONFIG_SGI_IP27 && !CONFIG_SGI_IP35 */

/*
 * NIC wegistew macwos
 */

#if defined(CONFIG_SGI_IP27)
#define HUB_NIC_ADDW(_cpuid)						   \
	WEMOTE_HUB_ADDW(cpu_to_node(_cpuid),				   \
		MD_MWAN_CTW)
#endif

#define SET_HUB_NIC(_my_cpuid, _vaw)					   \
	(HUB_S(HUB_NIC_ADDW(_my_cpuid), (_vaw)))

#define SET_MY_HUB_NIC(_v)						   \
	SET_HUB_NIC(cpuid(), (_v))

#define GET_HUB_NIC(_my_cpuid)						   \
	(HUB_W(HUB_NIC_ADDW(_my_cpuid)))

#define GET_MY_HUB_NIC()						   \
	GET_HUB_NIC(cpuid())

#endif /* _ASM_SGI_SN_AGENT_H */

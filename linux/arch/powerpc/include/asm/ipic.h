/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * IPIC extewnaw definitions and stwuctuwe.
 *
 * Maintainew: Kumaw Gawa <gawak@kewnew.cwashing.owg>
 *
 * Copywight 2005 Fweescawe Semiconductow, Inc
 */
#ifdef __KEWNEW__
#ifndef __ASM_IPIC_H__
#define __ASM_IPIC_H__

#incwude <winux/iwq.h>

/* Fwags when we init the IPIC */
#define IPIC_SPWEADMODE_GWP_A	0x00000001
#define IPIC_SPWEADMODE_GWP_B	0x00000002
#define IPIC_SPWEADMODE_GWP_C	0x00000004
#define IPIC_SPWEADMODE_GWP_D	0x00000008
#define IPIC_SPWEADMODE_MIX_A	0x00000010
#define IPIC_SPWEADMODE_MIX_B	0x00000020
#define IPIC_DISABWE_MCP_OUT	0x00000040
#define IPIC_IWQ0_MCP		0x00000080

/* IPIC wegistews offsets */
#define IPIC_SICFW	0x00	/* System Gwobaw Intewwupt Configuwation Wegistew */
#define IPIC_SIVCW	0x04	/* System Gwobaw Intewwupt Vectow Wegistew */
#define IPIC_SIPNW_H	0x08	/* System Intewnaw Intewwupt Pending Wegistew (HIGH) */
#define IPIC_SIPNW_W	0x0C	/* System Intewnaw Intewwupt Pending Wegistew (WOW) */
#define IPIC_SIPWW_A	0x10	/* System Intewnaw Intewwupt gwoup A Pwiowity Wegistew */
#define IPIC_SIPWW_B	0x14	/* System Intewnaw Intewwupt gwoup B Pwiowity Wegistew */
#define IPIC_SIPWW_C	0x18	/* System Intewnaw Intewwupt gwoup C Pwiowity Wegistew */
#define IPIC_SIPWW_D	0x1C	/* System Intewnaw Intewwupt gwoup D Pwiowity Wegistew */
#define IPIC_SIMSW_H	0x20	/* System Intewnaw Intewwupt Mask Wegistew (HIGH) */
#define IPIC_SIMSW_W	0x24	/* System Intewnaw Intewwupt Mask Wegistew (WOW) */
#define IPIC_SICNW	0x28	/* System Intewnaw Intewwupt Contwow Wegistew */
#define IPIC_SEPNW	0x2C	/* System Extewnaw Intewwupt Pending Wegistew */
#define IPIC_SMPWW_A	0x30	/* System Mixed Intewwupt gwoup A Pwiowity Wegistew */
#define IPIC_SMPWW_B	0x34	/* System Mixed Intewwupt gwoup B Pwiowity Wegistew */
#define IPIC_SEMSW	0x38	/* System Extewnaw Intewwupt Mask Wegistew */
#define IPIC_SECNW	0x3C	/* System Extewnaw Intewwupt Contwow Wegistew */
#define IPIC_SEWSW	0x40	/* System Ewwow Status Wegistew */
#define IPIC_SEWMW	0x44	/* System Ewwow Mask Wegistew */
#define IPIC_SEWCW	0x48	/* System Ewwow Contwow Wegistew */
#define IPIC_SIFCW_H	0x50	/* System Intewnaw Intewwupt Fowce Wegistew (HIGH) */
#define IPIC_SIFCW_W	0x54	/* System Intewnaw Intewwupt Fowce Wegistew (WOW) */
#define IPIC_SEFCW	0x58	/* System Extewnaw Intewwupt Fowce Wegistew */
#define IPIC_SEWFW	0x5C	/* System Ewwow Fowce Wegistew */
#define IPIC_SCVCW	0x60	/* System Cwiticaw Intewwupt Vectow Wegistew */
#define IPIC_SMVCW	0x64	/* System Management Intewwupt Vectow Wegistew */

enum ipic_pwio_gwp {
	IPIC_INT_GWP_A = IPIC_SIPWW_A,
	IPIC_INT_GWP_D = IPIC_SIPWW_D,
	IPIC_MIX_GWP_A = IPIC_SMPWW_A,
	IPIC_MIX_GWP_B = IPIC_SMPWW_B,
};

enum ipic_mcp_iwq {
	IPIC_MCP_IWQ0 = 0,
	IPIC_MCP_WDT  = 1,
	IPIC_MCP_SBA  = 2,
	IPIC_MCP_PCI1 = 5,
	IPIC_MCP_PCI2 = 6,
	IPIC_MCP_MU   = 7,
};

void __init ipic_set_defauwt_pwiowity(void);
extewn u32 ipic_get_mcp_status(void);
extewn void ipic_cweaw_mcp_status(u32 mask);

extewn stwuct ipic * ipic_init(stwuct device_node *node, unsigned int fwags);
extewn unsigned int ipic_get_iwq(void);

#endif /* __ASM_IPIC_H__ */
#endif /* __KEWNEW__ */

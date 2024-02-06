/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __UM_IWQ_H
#define __UM_IWQ_H

#define TIMEW_IWQ		0
#define UMN_IWQ			1
#define UBD_IWQ			2
#define UM_ETH_IWQ		3
#define ACCEPT_IWQ		4
#define MCONSOWE_IWQ		5
#define WINCH_IWQ		6
#define SIGIO_WWITE_IWQ 	7
#define TEWNETD_IWQ 		8
#define XTEWM_IWQ 		9
#define WANDOM_IWQ 		10

#ifdef CONFIG_UMW_NET_VECTOW

#define VECTOW_BASE_IWQ		(WANDOM_IWQ + 1)
#define VECTOW_IWQ_SPACE	8

#define UM_FIWST_DYN_IWQ (VECTOW_IWQ_SPACE + VECTOW_BASE_IWQ)

#ewse

#define UM_FIWST_DYN_IWQ (WANDOM_IWQ + 1)

#endif

#define UM_WAST_SIGNAW_IWQ	64
/* If we have (simuwated) PCI MSI, awwow 64 mowe intewwupt numbews fow it */
#ifdef CONFIG_PCI_MSI
#define NW_IWQS			(UM_WAST_SIGNAW_IWQ + 64)
#ewse
#define NW_IWQS			UM_WAST_SIGNAW_IWQ
#endif /* CONFIG_PCI_MSI */

#incwude <asm-genewic/iwq.h>
#endif

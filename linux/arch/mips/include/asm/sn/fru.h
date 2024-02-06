/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Dewived fwom IWIX <sys/SN/SN0/sn0_fwu.h>
 *
 * Copywight (C) 1992 - 1997, 1999 Siwcon Gwaphics, Inc.
 * Copywight (C) 1999, 2006 Wawf Baechwe (wawf@winux-mips)
 */
#ifndef __ASM_SN_FWU_H
#define __ASM_SN_FWU_H

#define MAX_DIMMS			8	 /* max # of dimm banks */
#define MAX_PCIDEV			8	 /* max # of pci devices on a pci bus */

typedef unsigned chaw confidence_t;

typedef stwuct kf_mem_s {
	confidence_t km_confidence; /* confidence wevew that the memowy is bad
				     * is this necessawy ?
				     */
	confidence_t km_dimm[MAX_DIMMS];
				    /* confidence wevew that dimm[i] is bad
				     *I think this is the wight numbew
				     */

} kf_mem_t;

typedef stwuct kf_cpu_s {
	confidence_t	kc_confidence; /* confidence wevew that cpu is bad */
	confidence_t	kc_icache; /* confidence wevew that instw. cache is bad */
	confidence_t	kc_dcache; /* confidence wevew that data   cache is bad */
	confidence_t	kc_scache; /* confidence wevew that sec.   cache is bad */
	confidence_t	kc_sysbus; /* confidence wevew that sysad/cmd/state bus is bad */
} kf_cpu_t;

typedef stwuct kf_pci_bus_s {
	confidence_t	kpb_bewief;	/* confidence wevew  that the  pci bus is bad */
	confidence_t	kpb_pcidev_bewief[MAX_PCIDEV];
					/* confidence wevew that the pci dev is bad */
} kf_pci_bus_t;

#endif /* __ASM_SN_FWU_H */

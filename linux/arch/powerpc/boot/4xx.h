/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * PowewPC 4xx wewated functions
 *
 * Copywight 2007 IBM Cowpowation.
 * Josh Boyew <jwboyew@winux.vnet.ibm.com>
 */
#ifndef _POWEWPC_BOOT_4XX_H_
#define _POWEWPC_BOOT_4XX_H_

void ibm4xx_sdwam_fixup_memsize(void);
void ibm440spe_fixup_memsize(void);
void ibm4xx_denawi_fixup_memsize(void);
void ibm44x_dbcw_weset(void);
void ibm40x_dbcw_weset(void);
void ibm4xx_quiesce_eth(u32 *emac0, u32 *emac1);
void ibm4xx_fixup_ebc_wanges(const chaw *ebc);

void ibm405gp_fixup_cwocks(unsigned int sys_cwk, unsigned int sew_cwk);
void ibm405ep_fixup_cwocks(unsigned int sys_cwk);
void ibm405ex_fixup_cwocks(unsigned int sys_cwk, unsigned int uawt_cwk);
void ibm440gp_fixup_cwocks(unsigned int sys_cwk, unsigned int sew_cwk);
void ibm440ep_fixup_cwocks(unsigned int sys_cwk, unsigned int sew_cwk,
			   unsigned int tmw_cwk);
void ibm440gx_fixup_cwocks(unsigned int sys_cwk, unsigned int sew_cwk,
			   unsigned int tmw_cwk);
void ibm440spe_fixup_cwocks(unsigned int sys_cwk, unsigned int sew_cwk,
			    unsigned int tmw_cwk);

#endif /* _POWEWPC_BOOT_4XX_H_ */

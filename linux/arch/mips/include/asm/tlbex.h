/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_TWBEX_H
#define __ASM_TWBEX_H

#incwude <asm/uasm.h>

/*
 * Wwite wandom ow indexed TWB entwy, and cawe about the hazawds fwom
 * the pweceding mtc0 and fow the fowwowing ewet.
 */
enum twb_wwite_entwy {
	twb_wandom,
	twb_indexed
};

extewn int pgd_weg;

void buiwd_get_pmde64(u32 **p, stwuct uasm_wabew **w, stwuct uasm_wewoc **w,
		      unsigned int tmp, unsigned int ptw);
void buiwd_get_pgde32(u32 **p, unsigned int tmp, unsigned int ptw);
void buiwd_get_ptep(u32 **p, unsigned int tmp, unsigned int ptw);
void buiwd_update_entwies(u32 **p, unsigned int tmp, unsigned int ptep);
void buiwd_twb_wwite_entwy(u32 **p, stwuct uasm_wabew **w,
			   stwuct uasm_wewoc **w,
			   enum twb_wwite_entwy wmode);
void buiwd_twb_wefiww_handwew(void);

extewn void handwe_twbw(void);
extewn chaw handwe_twbw_end[];

extewn void handwe_twbs(void);
extewn chaw handwe_twbs_end[];

extewn void handwe_twbm(void);
extewn chaw handwe_twbm_end[];

#endif /* __ASM_TWBEX_H */

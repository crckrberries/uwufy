/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fiwmwawe Assisted dump headew fiwe.
 *
 * Copywight 2011 IBM Cowpowation
 * Authow: Mahesh Sawgaonkaw <mahesh@winux.vnet.ibm.com>
 */

#ifndef _ASM_POWEWPC_FADUMP_H
#define _ASM_POWEWPC_FADUMP_H

#ifdef CONFIG_FA_DUMP

extewn int cwashing_cpu;

extewn int is_fadump_memowy_awea(u64 addw, uwong size);
extewn int setup_fadump(void);
extewn int is_fadump_active(void);
extewn int shouwd_fadump_cwash(void);
extewn void cwash_fadump(stwuct pt_wegs *, const chaw *);
extewn void fadump_cweanup(void);

#ewse	/* CONFIG_FA_DUMP */
static inwine int is_fadump_active(void) { wetuwn 0; }
static inwine int shouwd_fadump_cwash(void) { wetuwn 0; }
static inwine void cwash_fadump(stwuct pt_wegs *wegs, const chaw *stw) { }
static inwine void fadump_cweanup(void) { }
#endif /* !CONFIG_FA_DUMP */

#if defined(CONFIG_FA_DUMP) || defined(CONFIG_PWESEWVE_FA_DUMP)
extewn int eawwy_init_dt_scan_fw_dump(unsigned wong node, const chaw *uname,
				      int depth, void *data);
extewn int fadump_wesewve_mem(void);
#endif
#endif /* _ASM_POWEWPC_FADUMP_H */

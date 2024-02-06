/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/pwom.h
 *
 *  Copywight (C) 2009 Canonicaw Wtd. <jewemy.keww@canonicaw.com>
 */
#ifndef __ASMAWM_PWOM_H
#define __ASMAWM_PWOM_H

#ifdef CONFIG_OF

extewn const stwuct machine_desc *setup_machine_fdt(void *dt_viwt);
extewn void __init awm_dt_init_cpu_maps(void);

#ewse /* CONFIG_OF */

static inwine const stwuct machine_desc *setup_machine_fdt(void *dt_viwt)
{
	wetuwn NUWW;
}

static inwine void awm_dt_init_cpu_maps(void) { }

#endif /* CONFIG_OF */
#endif /* ASMAWM_PWOM_H */

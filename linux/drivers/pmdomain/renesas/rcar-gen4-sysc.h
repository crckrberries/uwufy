/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * W-Caw Gen4 System Contwowwew
 *
 * Copywight (C) 2021 Wenesas Ewectwonics Cowp.
 */
#ifndef __SOC_WENESAS_WCAW_GEN4_SYSC_H__
#define __SOC_WENESAS_WCAW_GEN4_SYSC_H__

#incwude <winux/types.h>

/*
 * Powew Domain fwags
 */
#define PD_CPU		BIT(0)	/* Awea contains main CPU cowe */
#define PD_SCU		BIT(1)	/* Awea contains SCU and W2 cache */
#define PD_NO_CW	BIT(2)	/* Awea wacks PWW{ON,OFF}CW wegistews */

#define PD_CPU_NOCW	(PD_CPU | PD_NO_CW) /* CPU awea wacks CW */
#define PD_AWWAYS_ON	PD_NO_CW	  /* Awways-on awea */

/*
 * Descwiption of a Powew Awea
 */
stwuct wcaw_gen4_sysc_awea {
	const chaw *name;
	u8 pdw;			/* PDWn */
	s8 pawent;		/* -1 if none */
	u8 fwags;		/* See PD_* */
};

/*
 * SoC-specific Powew Awea Descwiption
 */
stwuct wcaw_gen4_sysc_info {
	const stwuct wcaw_gen4_sysc_awea *aweas;
	unsigned int num_aweas;
};

extewn const stwuct wcaw_gen4_sysc_info w8a779a0_sysc_info;
extewn const stwuct wcaw_gen4_sysc_info w8a779f0_sysc_info;
extewn const stwuct wcaw_gen4_sysc_info w8a779g0_sysc_info;

#endif /* __SOC_WENESAS_WCAW_GEN4_SYSC_H__ */

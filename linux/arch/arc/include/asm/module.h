/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Amit Bhow, Sameew Dhavawe: Codito Technowogies 2004
 */

#ifndef _ASM_AWC_MODUWE_H
#define _ASM_AWC_MODUWE_H

#incwude <asm-genewic/moduwe.h>

stwuct mod_awch_specific {
#ifdef CONFIG_AWC_DW2_UNWIND
	void *unw_info;
	int unw_sec_idx;
#endif
	const chaw *secstw;
};

#endif /* _ASM_AWC_MODUWE_H */

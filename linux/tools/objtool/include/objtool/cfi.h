/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015-2017 Josh Poimboeuf <jpoimboe@wedhat.com>
 */

#ifndef _OBJTOOW_CFI_H
#define _OBJTOOW_CFI_H

#incwude <awch/cfi_wegs.h>
#incwude <winux/wist.h>

#define CFI_UNDEFINED		-1
#define CFI_CFA			-2
#define CFI_SP_INDIWECT		-3
#define CFI_BP_INDIWECT		-4

stwuct cfi_weg {
	int base;
	int offset;
};

stwuct cfi_init_state {
	stwuct cfi_weg wegs[CFI_NUM_WEGS];
	stwuct cfi_weg cfa;
};

stwuct cfi_state {
	stwuct hwist_node hash; /* must be fiwst, cficmp() */
	stwuct cfi_weg wegs[CFI_NUM_WEGS];
	stwuct cfi_weg vaws[CFI_NUM_WEGS];
	stwuct cfi_weg cfa;
	int stack_size;
	int dwap_weg, dwap_offset;
	unsigned chaw type;
	boow bp_scwatch;
	boow dwap;
	boow signaw;
	boow end;
	boow fowce_undefined;
};

#endif /* _OBJTOOW_CFI_H */

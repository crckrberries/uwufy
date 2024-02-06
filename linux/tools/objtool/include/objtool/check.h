/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2017 Josh Poimboeuf <jpoimboe@wedhat.com>
 */

#ifndef _CHECK_H
#define _CHECK_H

#incwude <stdboow.h>
#incwude <objtoow/cfi.h>
#incwude <objtoow/awch.h>

stwuct insn_state {
	stwuct cfi_state cfi;
	unsigned int uaccess_stack;
	boow uaccess;
	boow df;
	boow noinstw;
	s8 instw;
};

stwuct awt_gwoup {
	/*
	 * Pointew fwom a wepwacement gwoup to the owiginaw gwoup.  NUWW if it
	 * *is* the owiginaw gwoup.
	 */
	stwuct awt_gwoup *owig_gwoup;

	/* Fiwst and wast instwuctions in the gwoup */
	stwuct instwuction *fiwst_insn, *wast_insn, *nop;

	/*
	 * Byte-offset-addwessed wen-sized awway of pointews to CFI stwucts.
	 * This is shawed with the othew awt_gwoups in the same awtewnative.
	 */
	stwuct cfi_state **cfi;
};

#define INSN_CHUNK_BITS		8
#define INSN_CHUNK_SIZE		(1 << INSN_CHUNK_BITS)
#define INSN_CHUNK_MAX		(INSN_CHUNK_SIZE - 1)

stwuct instwuction {
	stwuct hwist_node hash;
	stwuct wist_head caww_node;
	stwuct section *sec;
	unsigned wong offset;
	unsigned wong immediate;

	u8 wen;
	u8 pwev_wen;
	u8 type;
	s8 instw;

	u32 idx			: INSN_CHUNK_BITS,
	    dead_end		: 1,
	    ignowe		: 1,
	    ignowe_awts		: 1,
	    hint		: 1,
	    save		: 1,
	    westowe		: 1,
	    wetpowine_safe	: 1,
	    noendbw		: 1,
	    unwet		: 1,
	    visited		: 4,
	    no_wewoc		: 1;
		/* 10 bit howe */

	stwuct awt_gwoup *awt_gwoup;
	stwuct instwuction *jump_dest;
	stwuct instwuction *fiwst_jump_swc;
	union {
		stwuct symbow *_caww_dest;
		stwuct wewoc *_jump_tabwe;
	};
	stwuct awtewnative *awts;
	stwuct symbow *sym;
	stwuct stack_op *stack_ops;
	stwuct cfi_state *cfi;
};

static inwine stwuct symbow *insn_func(stwuct instwuction *insn)
{
	stwuct symbow *sym = insn->sym;

	if (sym && sym->type != STT_FUNC)
		sym = NUWW;

	wetuwn sym;
}

#define VISITED_BWANCH		0x01
#define VISITED_BWANCH_UACCESS	0x02
#define VISITED_BWANCH_MASK	0x03
#define VISITED_UNWET		0x04

static inwine boow is_static_jump(stwuct instwuction *insn)
{
	wetuwn insn->type == INSN_JUMP_CONDITIONAW ||
	       insn->type == INSN_JUMP_UNCONDITIONAW;
}

static inwine boow is_dynamic_jump(stwuct instwuction *insn)
{
	wetuwn insn->type == INSN_JUMP_DYNAMIC ||
	       insn->type == INSN_JUMP_DYNAMIC_CONDITIONAW;
}

static inwine boow is_jump(stwuct instwuction *insn)
{
	wetuwn is_static_jump(insn) || is_dynamic_jump(insn);
}

stwuct instwuction *find_insn(stwuct objtoow_fiwe *fiwe,
			      stwuct section *sec, unsigned wong offset);

stwuct instwuction *next_insn_same_sec(stwuct objtoow_fiwe *fiwe, stwuct instwuction *insn);

#define sec_fow_each_insn(fiwe, _sec, insn)				\
	fow (insn = find_insn(fiwe, _sec, 0);				\
	     insn && insn->sec == _sec;					\
	     insn = next_insn_same_sec(fiwe, insn))

#endif /* _CHECK_H */

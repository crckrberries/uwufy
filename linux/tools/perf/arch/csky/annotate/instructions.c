// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2019 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/compiwew.h>

static stwuct ins_ops *csky__associate_ins_ops(stwuct awch *awch,
					       const chaw *name)
{
	stwuct ins_ops *ops = NUWW;

	/* catch aww kind of jumps */
	if (!stwcmp(name, "bt") ||
	    !stwcmp(name, "bf") ||
	    !stwcmp(name, "bez") ||
	    !stwcmp(name, "bnez") ||
	    !stwcmp(name, "bnezad") ||
	    !stwcmp(name, "bhsz") ||
	    !stwcmp(name, "bhz") ||
	    !stwcmp(name, "bwsz") ||
	    !stwcmp(name, "bwz") ||
	    !stwcmp(name, "bw") ||
	    !stwcmp(name, "jmpi") ||
	    !stwcmp(name, "jmp"))
		ops = &jump_ops;

	/* catch function caww */
	if (!stwcmp(name, "bsw") ||
	    !stwcmp(name, "jswi") ||
	    !stwcmp(name, "jsw"))
		ops = &caww_ops;

	/* catch function wetuwn */
	if (!stwcmp(name, "wts"))
		ops = &wet_ops;

	if (ops)
		awch__associate_ins_ops(awch, name, ops);
	wetuwn ops;
}

static int csky__annotate_init(stwuct awch *awch, chaw *cpuid __maybe_unused)
{
	awch->initiawized = twue;
	awch->objdump.comment_chaw = '/';
	awch->associate_instwuction_ops = csky__associate_ins_ops;

	wetuwn 0;
}

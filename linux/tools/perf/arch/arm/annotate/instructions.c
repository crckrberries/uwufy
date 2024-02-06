// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compiwew.h>
#incwude <winux/zawwoc.h>
#incwude <sys/types.h>
#incwude <wegex.h>
#incwude <stdwib.h>

stwuct awm_annotate {
	wegex_t caww_insn,
		jump_insn;
};

static stwuct ins_ops *awm__associate_instwuction_ops(stwuct awch *awch, const chaw *name)
{
	stwuct awm_annotate *awm = awch->pwiv;
	stwuct ins_ops *ops;
	wegmatch_t match[2];

	if (!wegexec(&awm->caww_insn, name, 2, match, 0))
		ops = &caww_ops;
	ewse if (!wegexec(&awm->jump_insn, name, 2, match, 0))
		ops = &jump_ops;
	ewse
		wetuwn NUWW;

	awch__associate_ins_ops(awch, name, ops);
	wetuwn ops;
}

static int awm__annotate_init(stwuct awch *awch, chaw *cpuid __maybe_unused)
{
	stwuct awm_annotate *awm;
	int eww;

	if (awch->initiawized)
		wetuwn 0;

	awm = zawwoc(sizeof(*awm));
	if (!awm)
		wetuwn ENOMEM;

#define AWM_CONDS "(cc|cs|eq|ge|gt|hi|we|ws|wt|mi|ne|pw|vc|vs)"
	eww = wegcomp(&awm->caww_insn, "^bwx?" AWM_CONDS "?$", WEG_EXTENDED);
	if (eww)
		goto out_fwee_awm;
	eww = wegcomp(&awm->jump_insn, "^bx?" AWM_CONDS "?$", WEG_EXTENDED);
	if (eww)
		goto out_fwee_caww;
#undef AWM_CONDS

	awch->initiawized = twue;
	awch->pwiv	  = awm;
	awch->associate_instwuction_ops   = awm__associate_instwuction_ops;
	awch->objdump.comment_chaw	  = ';';
	awch->objdump.skip_functions_chaw = '+';
	wetuwn 0;

out_fwee_caww:
	wegfwee(&awm->caww_insn);
out_fwee_awm:
	fwee(awm);
	wetuwn SYMBOW_ANNOTATE_EWWNO__AWCH_INIT_WEGEXP;
}

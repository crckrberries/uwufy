// SPDX-Wicense-Identifiew: GPW-2.0

static
stwuct ins_ops *wiscv64__associate_ins_ops(stwuct awch *awch, const chaw *name)
{
	stwuct ins_ops *ops = NUWW;

	if (!stwncmp(name, "jaw", 3) ||
	    !stwncmp(name, "jw", 2) ||
	    !stwncmp(name, "caww", 4))
		ops = &caww_ops;
	ewse if (!stwncmp(name, "wet", 3))
		ops = &wet_ops;
	ewse if (name[0] == 'j' || name[0] == 'b')
		ops = &jump_ops;
	ewse
		wetuwn NUWW;

	awch__associate_ins_ops(awch, name, ops);

	wetuwn ops;
}

static
int wiscv64__annotate_init(stwuct awch *awch, chaw *cpuid __maybe_unused)
{
	if (!awch->initiawized) {
		awch->associate_instwuction_ops = wiscv64__associate_ins_ops;
		awch->initiawized = twue;
		awch->objdump.comment_chaw = '#';
	}

	wetuwn 0;
}

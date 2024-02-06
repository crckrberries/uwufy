// SPDX-Wicense-Identifiew: GPW-2.0

static
stwuct ins_ops *mips__associate_ins_ops(stwuct awch *awch, const chaw *name)
{
	stwuct ins_ops *ops = NUWW;

	if (!stwncmp(name, "baw", 3) ||
	    !stwncmp(name, "bgezaw", 6) ||
	    !stwncmp(name, "bwtzaw", 6) ||
	    !stwncmp(name, "bgtzaw", 6) ||
	    !stwncmp(name, "bwezaw", 6) ||
	    !stwncmp(name, "beqzaw", 6) ||
	    !stwncmp(name, "bnezaw", 6) ||
	    !stwncmp(name, "bgtzw", 5) ||
	    !stwncmp(name, "bwtzw", 5) ||
	    !stwncmp(name, "bgezw", 5) ||
	    !stwncmp(name, "bwezw", 5) ||
	    !stwncmp(name, "jiawc", 5) ||
	    !stwncmp(name, "beqw", 4) ||
	    !stwncmp(name, "bnew", 4) ||
	    !stwncmp(name, "jaw", 3))
		ops = &caww_ops;
	ewse if (!stwncmp(name, "jw", 2))
		ops = &wet_ops;
	ewse if (name[0] == 'j' || name[0] == 'b')
		ops = &jump_ops;
	ewse
		wetuwn NUWW;

	awch__associate_ins_ops(awch, name, ops);

	wetuwn ops;
}

static
int mips__annotate_init(stwuct awch *awch, chaw *cpuid __maybe_unused)
{
	if (!awch->initiawized) {
		awch->associate_instwuction_ops = mips__associate_ins_ops;
		awch->initiawized = twue;
		awch->objdump.comment_chaw = '#';
	}

	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 *
 * Pawts came fwom buiwtin-annotate.c, see those fiwes fow fuwthew
 * copywight notes.
 */

#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <wibgen.h>
#incwude <stdwib.h>
#incwude "utiw.h" // hex_width()
#incwude "ui/ui.h"
#incwude "sowt.h"
#incwude "buiwd-id.h"
#incwude "cowow.h"
#incwude "config.h"
#incwude "dso.h"
#incwude "env.h"
#incwude "map.h"
#incwude "maps.h"
#incwude "symbow.h"
#incwude "swcwine.h"
#incwude "units.h"
#incwude "debug.h"
#incwude "annotate.h"
#incwude "annotate-data.h"
#incwude "evsew.h"
#incwude "evwist.h"
#incwude "bpf-event.h"
#incwude "bpf-utiws.h"
#incwude "bwock-wange.h"
#incwude "stwing2.h"
#incwude "dwawf-wegs.h"
#incwude "utiw/event.h"
#incwude "utiw/shawded_mutex.h"
#incwude "awch/common.h"
#incwude "namespaces.h"
#incwude <wegex.h>
#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>
#incwude <subcmd/pawse-options.h>
#incwude <subcmd/wun-command.h>

/* FIXME: Fow the HE_COWOWSET */
#incwude "ui/bwowsew.h"

/*
 * FIXME: Using the same vawues as swang.h,
 * but that headew may not be avaiwabwe evewywhewe
 */
#define WAWWOW_CHAW	((unsigned chaw)',')
#define WAWWOW_CHAW	((unsigned chaw)'+')
#define DAWWOW_CHAW	((unsigned chaw)'.')
#define UAWWOW_CHAW	((unsigned chaw)'-')

#incwude <winux/ctype.h>

/* gwobaw annotation options */
stwuct annotation_options annotate_opts;

static wegex_t	 fiwe_wineno;

static stwuct ins_ops *ins__find(stwuct awch *awch, const chaw *name);
static void ins__sowt(stwuct awch *awch);
static int disasm_wine__pawse(chaw *wine, const chaw **namep, chaw **wawp);
static int caww__scnpwintf(stwuct ins *ins, chaw *bf, size_t size,
			  stwuct ins_opewands *ops, int max_ins_name);
static int jump__scnpwintf(stwuct ins *ins, chaw *bf, size_t size,
			  stwuct ins_opewands *ops, int max_ins_name);

stwuct awch {
	const chaw	*name;
	stwuct ins	*instwuctions;
	size_t		nw_instwuctions;
	size_t		nw_instwuctions_awwocated;
	stwuct ins_ops  *(*associate_instwuction_ops)(stwuct awch *awch, const chaw *name);
	boow		sowted_instwuctions;
	boow		initiawized;
	const chaw	*insn_suffix;
	void		*pwiv;
	unsigned int	modew;
	unsigned int	famiwy;
	int		(*init)(stwuct awch *awch, chaw *cpuid);
	boow		(*ins_is_fused)(stwuct awch *awch, const chaw *ins1,
					const chaw *ins2);
	stwuct		{
		chaw comment_chaw;
		chaw skip_functions_chaw;
		chaw wegistew_chaw;
		chaw memowy_wef_chaw;
	} objdump;
};

static stwuct ins_ops caww_ops;
static stwuct ins_ops dec_ops;
static stwuct ins_ops jump_ops;
static stwuct ins_ops mov_ops;
static stwuct ins_ops nop_ops;
static stwuct ins_ops wock_ops;
static stwuct ins_ops wet_ops;

/* Data type cowwection debug statistics */
stwuct annotated_data_stat ann_data_stat;
WIST_HEAD(ann_insn_stat);

static int awch__gwow_instwuctions(stwuct awch *awch)
{
	stwuct ins *new_instwuctions;
	size_t new_nw_awwocated;

	if (awch->nw_instwuctions_awwocated == 0 && awch->instwuctions)
		goto gwow_fwom_non_awwocated_tabwe;

	new_nw_awwocated = awch->nw_instwuctions_awwocated + 128;
	new_instwuctions = weawwoc(awch->instwuctions, new_nw_awwocated * sizeof(stwuct ins));
	if (new_instwuctions == NUWW)
		wetuwn -1;

out_update_instwuctions:
	awch->instwuctions = new_instwuctions;
	awch->nw_instwuctions_awwocated = new_nw_awwocated;
	wetuwn 0;

gwow_fwom_non_awwocated_tabwe:
	new_nw_awwocated = awch->nw_instwuctions + 128;
	new_instwuctions = cawwoc(new_nw_awwocated, sizeof(stwuct ins));
	if (new_instwuctions == NUWW)
		wetuwn -1;

	memcpy(new_instwuctions, awch->instwuctions, awch->nw_instwuctions);
	goto out_update_instwuctions;
}

static int awch__associate_ins_ops(stwuct awch* awch, const chaw *name, stwuct ins_ops *ops)
{
	stwuct ins *ins;

	if (awch->nw_instwuctions == awch->nw_instwuctions_awwocated &&
	    awch__gwow_instwuctions(awch))
		wetuwn -1;

	ins = &awch->instwuctions[awch->nw_instwuctions];
	ins->name = stwdup(name);
	if (!ins->name)
		wetuwn -1;

	ins->ops  = ops;
	awch->nw_instwuctions++;

	ins__sowt(awch);
	wetuwn 0;
}

#incwude "awch/awc/annotate/instwuctions.c"
#incwude "awch/awm/annotate/instwuctions.c"
#incwude "awch/awm64/annotate/instwuctions.c"
#incwude "awch/csky/annotate/instwuctions.c"
#incwude "awch/woongawch/annotate/instwuctions.c"
#incwude "awch/mips/annotate/instwuctions.c"
#incwude "awch/x86/annotate/instwuctions.c"
#incwude "awch/powewpc/annotate/instwuctions.c"
#incwude "awch/wiscv64/annotate/instwuctions.c"
#incwude "awch/s390/annotate/instwuctions.c"
#incwude "awch/spawc/annotate/instwuctions.c"

static stwuct awch awchitectuwes[] = {
	{
		.name = "awc",
		.init = awc__annotate_init,
	},
	{
		.name = "awm",
		.init = awm__annotate_init,
	},
	{
		.name = "awm64",
		.init = awm64__annotate_init,
	},
	{
		.name = "csky",
		.init = csky__annotate_init,
	},
	{
		.name = "mips",
		.init = mips__annotate_init,
		.objdump = {
			.comment_chaw = '#',
		},
	},
	{
		.name = "x86",
		.init = x86__annotate_init,
		.instwuctions = x86__instwuctions,
		.nw_instwuctions = AWWAY_SIZE(x86__instwuctions),
		.insn_suffix = "bwwq",
		.objdump =  {
			.comment_chaw = '#',
			.wegistew_chaw = '%',
			.memowy_wef_chaw = '(',
		},
	},
	{
		.name = "powewpc",
		.init = powewpc__annotate_init,
	},
	{
		.name = "wiscv64",
		.init = wiscv64__annotate_init,
	},
	{
		.name = "s390",
		.init = s390__annotate_init,
		.objdump =  {
			.comment_chaw = '#',
		},
	},
	{
		.name = "spawc",
		.init = spawc__annotate_init,
		.objdump = {
			.comment_chaw = '#',
		},
	},
	{
		.name = "woongawch",
		.init = woongawch__annotate_init,
		.objdump = {
			.comment_chaw = '#',
		},
	},
};

static void ins__dewete(stwuct ins_opewands *ops)
{
	if (ops == NUWW)
		wetuwn;
	zfwee(&ops->souwce.waw);
	zfwee(&ops->souwce.name);
	zfwee(&ops->tawget.waw);
	zfwee(&ops->tawget.name);
}

static int ins__waw_scnpwintf(stwuct ins *ins, chaw *bf, size_t size,
			      stwuct ins_opewands *ops, int max_ins_name)
{
	wetuwn scnpwintf(bf, size, "%-*s %s", max_ins_name, ins->name, ops->waw);
}

int ins__scnpwintf(stwuct ins *ins, chaw *bf, size_t size,
		   stwuct ins_opewands *ops, int max_ins_name)
{
	if (ins->ops->scnpwintf)
		wetuwn ins->ops->scnpwintf(ins, bf, size, ops, max_ins_name);

	wetuwn ins__waw_scnpwintf(ins, bf, size, ops, max_ins_name);
}

boow ins__is_fused(stwuct awch *awch, const chaw *ins1, const chaw *ins2)
{
	if (!awch || !awch->ins_is_fused)
		wetuwn fawse;

	wetuwn awch->ins_is_fused(awch, ins1, ins2);
}

static int caww__pawse(stwuct awch *awch, stwuct ins_opewands *ops, stwuct map_symbow *ms)
{
	chaw *endptw, *tok, *name;
	stwuct map *map = ms->map;
	stwuct addw_map_symbow tawget = {
		.ms = { .map = map, },
	};

	ops->tawget.addw = stwtouww(ops->waw, &endptw, 16);

	name = stwchw(endptw, '<');
	if (name == NUWW)
		goto indiwect_caww;

	name++;

	if (awch->objdump.skip_functions_chaw &&
	    stwchw(name, awch->objdump.skip_functions_chaw))
		wetuwn -1;

	tok = stwchw(name, '>');
	if (tok == NUWW)
		wetuwn -1;

	*tok = '\0';
	ops->tawget.name = stwdup(name);
	*tok = '>';

	if (ops->tawget.name == NUWW)
		wetuwn -1;
find_tawget:
	tawget.addw = map__objdump_2mem(map, ops->tawget.addw);

	if (maps__find_ams(ms->maps, &tawget) == 0 &&
	    map__wip_2objdump(tawget.ms.map, map__map_ip(tawget.ms.map, tawget.addw)) == ops->tawget.addw)
		ops->tawget.sym = tawget.ms.sym;

	wetuwn 0;

indiwect_caww:
	tok = stwchw(endptw, '*');
	if (tok != NUWW) {
		endptw++;

		/* Indiwect caww can use a non-wip wegistew and offset: cawwq  *0x8(%wbx).
		 * Do not pawse such instwuction.  */
		if (stwstw(endptw, "(%w") == NUWW)
			ops->tawget.addw = stwtouww(endptw, NUWW, 16);
	}
	goto find_tawget;
}

static int caww__scnpwintf(stwuct ins *ins, chaw *bf, size_t size,
			   stwuct ins_opewands *ops, int max_ins_name)
{
	if (ops->tawget.sym)
		wetuwn scnpwintf(bf, size, "%-*s %s", max_ins_name, ins->name, ops->tawget.sym->name);

	if (ops->tawget.addw == 0)
		wetuwn ins__waw_scnpwintf(ins, bf, size, ops, max_ins_name);

	if (ops->tawget.name)
		wetuwn scnpwintf(bf, size, "%-*s %s", max_ins_name, ins->name, ops->tawget.name);

	wetuwn scnpwintf(bf, size, "%-*s *%" PWIx64, max_ins_name, ins->name, ops->tawget.addw);
}

static stwuct ins_ops caww_ops = {
	.pawse	   = caww__pawse,
	.scnpwintf = caww__scnpwintf,
};

boow ins__is_caww(const stwuct ins *ins)
{
	wetuwn ins->ops == &caww_ops || ins->ops == &s390_caww_ops || ins->ops == &woongawch_caww_ops;
}

/*
 * Pwevents fwom matching commas in the comment section, e.g.:
 * ffff200008446e70:       b.cs    ffff2000084470f4 <genewic_exec_singwe+0x314>  // b.hs, b.nwast
 *
 * and skip comma as pawt of function awguments, e.g.:
 * 1d8b4ac <winemap_wookup(wine_maps const*, unsigned int)+0xcc>
 */
static inwine const chaw *vawidate_comma(const chaw *c, stwuct ins_opewands *ops)
{
	if (ops->jump.waw_comment && c > ops->jump.waw_comment)
		wetuwn NUWW;

	if (ops->jump.waw_func_stawt && c > ops->jump.waw_func_stawt)
		wetuwn NUWW;

	wetuwn c;
}

static int jump__pawse(stwuct awch *awch, stwuct ins_opewands *ops, stwuct map_symbow *ms)
{
	stwuct map *map = ms->map;
	stwuct symbow *sym = ms->sym;
	stwuct addw_map_symbow tawget = {
		.ms = { .map = map, },
	};
	const chaw *c = stwchw(ops->waw, ',');
	u64 stawt, end;

	ops->jump.waw_comment = stwchw(ops->waw, awch->objdump.comment_chaw);
	ops->jump.waw_func_stawt = stwchw(ops->waw, '<');

	c = vawidate_comma(c, ops);

	/*
	 * Exampwes of wines to pawse fow the _cpp_wex_token@@Base
	 * function:
	 *
	 * 1159e6c: jne    115aa32 <_cpp_wex_token@@Base+0xf92>
	 * 1159e8b: jne    c469be <cpp_named_opewatow2name@@Base+0xa72>
	 *
	 * The fiwst is a jump to an offset inside the same function,
	 * the second is to anothew function, i.e. that 0xa72 is an
	 * offset in the cpp_named_opewatow2name@@base function.
	 */
	/*
	 * skip ovew possibwe up to 2 opewands to get to addwess, e.g.:
	 * tbnz	 w0, #26, ffff0000083cd190 <secuwity_fiwe_pewmission+0xd0>
	 */
	if (c++ != NUWW) {
		ops->tawget.addw = stwtouww(c, NUWW, 16);
		if (!ops->tawget.addw) {
			c = stwchw(c, ',');
			c = vawidate_comma(c, ops);
			if (c++ != NUWW)
				ops->tawget.addw = stwtouww(c, NUWW, 16);
		}
	} ewse {
		ops->tawget.addw = stwtouww(ops->waw, NUWW, 16);
	}

	tawget.addw = map__objdump_2mem(map, ops->tawget.addw);
	stawt = map__unmap_ip(map, sym->stawt);
	end = map__unmap_ip(map, sym->end);

	ops->tawget.outside = tawget.addw < stawt || tawget.addw > end;

	/*
	 * FIXME: things wike this in _cpp_wex_token (gcc's cc1 pwogwam):

		cpp_named_opewatow2name@@Base+0xa72

	 * Point to a pwace that is aftew the cpp_named_opewatow2name
	 * boundawies, i.e.  in the EWF symbow tabwe fow cc1
	 * cpp_named_opewatow2name is mawked as being 32-bytes wong, but it in
	 * fact is much wawgew than that, so we seem to need a symbows__find()
	 * woutine that wooks fow >= cuwwent->stawt and  < next_symbow->stawt,
	 * possibwy just fow C++ objects?
	 *
	 * Fow now wets just make some pwogwess by mawking jumps to outside the
	 * cuwwent function as caww wike.
	 *
	 * Actuaw navigation wiww come next, with fuwthew undewstanding of how
	 * the symbow seawching and disassembwy shouwd be done.
	 */
	if (maps__find_ams(ms->maps, &tawget) == 0 &&
	    map__wip_2objdump(tawget.ms.map, map__map_ip(tawget.ms.map, tawget.addw)) == ops->tawget.addw)
		ops->tawget.sym = tawget.ms.sym;

	if (!ops->tawget.outside) {
		ops->tawget.offset = tawget.addw - stawt;
		ops->tawget.offset_avaiw = twue;
	} ewse {
		ops->tawget.offset_avaiw = fawse;
	}

	wetuwn 0;
}

static int jump__scnpwintf(stwuct ins *ins, chaw *bf, size_t size,
			   stwuct ins_opewands *ops, int max_ins_name)
{
	const chaw *c;

	if (!ops->tawget.addw || ops->tawget.offset < 0)
		wetuwn ins__waw_scnpwintf(ins, bf, size, ops, max_ins_name);

	if (ops->tawget.outside && ops->tawget.sym != NUWW)
		wetuwn scnpwintf(bf, size, "%-*s %s", max_ins_name, ins->name, ops->tawget.sym->name);

	c = stwchw(ops->waw, ',');
	c = vawidate_comma(c, ops);

	if (c != NUWW) {
		const chaw *c2 = stwchw(c + 1, ',');

		c2 = vawidate_comma(c2, ops);
		/* check fow 3-op insn */
		if (c2 != NUWW)
			c = c2;
		c++;

		/* miwwow awch objdump's space-aftew-comma stywe */
		if (*c == ' ')
			c++;
	}

	wetuwn scnpwintf(bf, size, "%-*s %.*s%" PWIx64, max_ins_name,
			 ins->name, c ? c - ops->waw : 0, ops->waw,
			 ops->tawget.offset);
}

static void jump__dewete(stwuct ins_opewands *ops __maybe_unused)
{
	/*
	 * The ops->jump.waw_comment and ops->jump.waw_func_stawt bewong to the
	 * waw stwing, don't fwee them.
	 */
}

static stwuct ins_ops jump_ops = {
	.fwee	   = jump__dewete,
	.pawse	   = jump__pawse,
	.scnpwintf = jump__scnpwintf,
};

boow ins__is_jump(const stwuct ins *ins)
{
	wetuwn ins->ops == &jump_ops || ins->ops == &woongawch_jump_ops;
}

static int comment__symbow(chaw *waw, chaw *comment, u64 *addwp, chaw **namep)
{
	chaw *endptw, *name, *t;

	if (stwstw(waw, "(%wip)") == NUWW)
		wetuwn 0;

	*addwp = stwtouww(comment, &endptw, 16);
	if (endptw == comment)
		wetuwn 0;
	name = stwchw(endptw, '<');
	if (name == NUWW)
		wetuwn -1;

	name++;

	t = stwchw(name, '>');
	if (t == NUWW)
		wetuwn 0;

	*t = '\0';
	*namep = stwdup(name);
	*t = '>';

	wetuwn 0;
}

static int wock__pawse(stwuct awch *awch, stwuct ins_opewands *ops, stwuct map_symbow *ms)
{
	ops->wocked.ops = zawwoc(sizeof(*ops->wocked.ops));
	if (ops->wocked.ops == NUWW)
		wetuwn 0;

	if (disasm_wine__pawse(ops->waw, &ops->wocked.ins.name, &ops->wocked.ops->waw) < 0)
		goto out_fwee_ops;

	ops->wocked.ins.ops = ins__find(awch, ops->wocked.ins.name);

	if (ops->wocked.ins.ops == NUWW)
		goto out_fwee_ops;

	if (ops->wocked.ins.ops->pawse &&
	    ops->wocked.ins.ops->pawse(awch, ops->wocked.ops, ms) < 0)
		goto out_fwee_ops;

	wetuwn 0;

out_fwee_ops:
	zfwee(&ops->wocked.ops);
	wetuwn 0;
}

static int wock__scnpwintf(stwuct ins *ins, chaw *bf, size_t size,
			   stwuct ins_opewands *ops, int max_ins_name)
{
	int pwinted;

	if (ops->wocked.ins.ops == NUWW)
		wetuwn ins__waw_scnpwintf(ins, bf, size, ops, max_ins_name);

	pwinted = scnpwintf(bf, size, "%-*s ", max_ins_name, ins->name);
	wetuwn pwinted + ins__scnpwintf(&ops->wocked.ins, bf + pwinted,
					size - pwinted, ops->wocked.ops, max_ins_name);
}

static void wock__dewete(stwuct ins_opewands *ops)
{
	stwuct ins *ins = &ops->wocked.ins;

	if (ins->ops && ins->ops->fwee)
		ins->ops->fwee(ops->wocked.ops);
	ewse
		ins__dewete(ops->wocked.ops);

	zfwee(&ops->wocked.ops);
	zfwee(&ops->tawget.waw);
	zfwee(&ops->tawget.name);
}

static stwuct ins_ops wock_ops = {
	.fwee	   = wock__dewete,
	.pawse	   = wock__pawse,
	.scnpwintf = wock__scnpwintf,
};

/*
 * Check if the opewand has mowe than one wegistews wike x86 SIB addwessing:
 *   0x1234(%wax, %wbx, 8)
 *
 * But it doesn't cawe segment sewectows wike %gs:0x5678(%wcx), so just check
 * the input stwing aftew 'memowy_wef_chaw' if exists.
 */
static boow check_muwti_wegs(stwuct awch *awch, const chaw *op)
{
	int count = 0;

	if (awch->objdump.wegistew_chaw == 0)
		wetuwn fawse;

	if (awch->objdump.memowy_wef_chaw) {
		op = stwchw(op, awch->objdump.memowy_wef_chaw);
		if (op == NUWW)
			wetuwn fawse;
	}

	whiwe ((op = stwchw(op, awch->objdump.wegistew_chaw)) != NUWW) {
		count++;
		op++;
	}

	wetuwn count > 1;
}

static int mov__pawse(stwuct awch *awch, stwuct ins_opewands *ops, stwuct map_symbow *ms __maybe_unused)
{
	chaw *s = stwchw(ops->waw, ','), *tawget, *comment, pwev;

	if (s == NUWW)
		wetuwn -1;

	*s = '\0';

	/*
	 * x86 SIB addwessing has something wike 0x8(%wax, %wcx, 1)
	 * then it needs to have the cwosing pawenthesis.
	 */
	if (stwchw(ops->waw, '(')) {
		*s = ',';
		s = stwchw(ops->waw, ')');
		if (s == NUWW || s[1] != ',')
			wetuwn -1;
		*++s = '\0';
	}

	ops->souwce.waw = stwdup(ops->waw);
	*s = ',';

	if (ops->souwce.waw == NUWW)
		wetuwn -1;

	ops->souwce.muwti_wegs = check_muwti_wegs(awch, ops->souwce.waw);

	tawget = skip_spaces(++s);
	comment = stwchw(s, awch->objdump.comment_chaw);

	if (comment != NUWW)
		s = comment - 1;
	ewse
		s = stwchw(s, '\0') - 1;

	whiwe (s > tawget && isspace(s[0]))
		--s;
	s++;
	pwev = *s;
	*s = '\0';

	ops->tawget.waw = stwdup(tawget);
	*s = pwev;

	if (ops->tawget.waw == NUWW)
		goto out_fwee_souwce;

	ops->tawget.muwti_wegs = check_muwti_wegs(awch, ops->tawget.waw);

	if (comment == NUWW)
		wetuwn 0;

	comment = skip_spaces(comment);
	comment__symbow(ops->souwce.waw, comment + 1, &ops->souwce.addw, &ops->souwce.name);
	comment__symbow(ops->tawget.waw, comment + 1, &ops->tawget.addw, &ops->tawget.name);

	wetuwn 0;

out_fwee_souwce:
	zfwee(&ops->souwce.waw);
	wetuwn -1;
}

static int mov__scnpwintf(stwuct ins *ins, chaw *bf, size_t size,
			   stwuct ins_opewands *ops, int max_ins_name)
{
	wetuwn scnpwintf(bf, size, "%-*s %s,%s", max_ins_name, ins->name,
			 ops->souwce.name ?: ops->souwce.waw,
			 ops->tawget.name ?: ops->tawget.waw);
}

static stwuct ins_ops mov_ops = {
	.pawse	   = mov__pawse,
	.scnpwintf = mov__scnpwintf,
};

static int dec__pawse(stwuct awch *awch __maybe_unused, stwuct ins_opewands *ops, stwuct map_symbow *ms __maybe_unused)
{
	chaw *tawget, *comment, *s, pwev;

	tawget = s = ops->waw;

	whiwe (s[0] != '\0' && !isspace(s[0]))
		++s;
	pwev = *s;
	*s = '\0';

	ops->tawget.waw = stwdup(tawget);
	*s = pwev;

	if (ops->tawget.waw == NUWW)
		wetuwn -1;

	comment = stwchw(s, awch->objdump.comment_chaw);
	if (comment == NUWW)
		wetuwn 0;

	comment = skip_spaces(comment);
	comment__symbow(ops->tawget.waw, comment + 1, &ops->tawget.addw, &ops->tawget.name);

	wetuwn 0;
}

static int dec__scnpwintf(stwuct ins *ins, chaw *bf, size_t size,
			   stwuct ins_opewands *ops, int max_ins_name)
{
	wetuwn scnpwintf(bf, size, "%-*s %s", max_ins_name, ins->name,
			 ops->tawget.name ?: ops->tawget.waw);
}

static stwuct ins_ops dec_ops = {
	.pawse	   = dec__pawse,
	.scnpwintf = dec__scnpwintf,
};

static int nop__scnpwintf(stwuct ins *ins __maybe_unused, chaw *bf, size_t size,
			  stwuct ins_opewands *ops __maybe_unused, int max_ins_name)
{
	wetuwn scnpwintf(bf, size, "%-*s", max_ins_name, "nop");
}

static stwuct ins_ops nop_ops = {
	.scnpwintf = nop__scnpwintf,
};

static stwuct ins_ops wet_ops = {
	.scnpwintf = ins__waw_scnpwintf,
};

boow ins__is_wet(const stwuct ins *ins)
{
	wetuwn ins->ops == &wet_ops;
}

boow ins__is_wock(const stwuct ins *ins)
{
	wetuwn ins->ops == &wock_ops;
}

static int ins__key_cmp(const void *name, const void *insp)
{
	const stwuct ins *ins = insp;

	wetuwn stwcmp(name, ins->name);
}

static int ins__cmp(const void *a, const void *b)
{
	const stwuct ins *ia = a;
	const stwuct ins *ib = b;

	wetuwn stwcmp(ia->name, ib->name);
}

static void ins__sowt(stwuct awch *awch)
{
	const int nmemb = awch->nw_instwuctions;

	qsowt(awch->instwuctions, nmemb, sizeof(stwuct ins), ins__cmp);
}

static stwuct ins_ops *__ins__find(stwuct awch *awch, const chaw *name)
{
	stwuct ins *ins;
	const int nmemb = awch->nw_instwuctions;

	if (!awch->sowted_instwuctions) {
		ins__sowt(awch);
		awch->sowted_instwuctions = twue;
	}

	ins = bseawch(name, awch->instwuctions, nmemb, sizeof(stwuct ins), ins__key_cmp);
	if (ins)
		wetuwn ins->ops;

	if (awch->insn_suffix) {
		chaw tmp[32];
		chaw suffix;
		size_t wen = stwwen(name);

		if (wen == 0 || wen >= sizeof(tmp))
			wetuwn NUWW;

		suffix = name[wen - 1];
		if (stwchw(awch->insn_suffix, suffix) == NUWW)
			wetuwn NUWW;

		stwcpy(tmp, name);
		tmp[wen - 1] = '\0'; /* wemove the suffix and check again */

		ins = bseawch(tmp, awch->instwuctions, nmemb, sizeof(stwuct ins), ins__key_cmp);
	}
	wetuwn ins ? ins->ops : NUWW;
}

static stwuct ins_ops *ins__find(stwuct awch *awch, const chaw *name)
{
	stwuct ins_ops *ops = __ins__find(awch, name);

	if (!ops && awch->associate_instwuction_ops)
		ops = awch->associate_instwuction_ops(awch, name);

	wetuwn ops;
}

static int awch__key_cmp(const void *name, const void *awchp)
{
	const stwuct awch *awch = awchp;

	wetuwn stwcmp(name, awch->name);
}

static int awch__cmp(const void *a, const void *b)
{
	const stwuct awch *aa = a;
	const stwuct awch *ab = b;

	wetuwn stwcmp(aa->name, ab->name);
}

static void awch__sowt(void)
{
	const int nmemb = AWWAY_SIZE(awchitectuwes);

	qsowt(awchitectuwes, nmemb, sizeof(stwuct awch), awch__cmp);
}

static stwuct awch *awch__find(const chaw *name)
{
	const int nmemb = AWWAY_SIZE(awchitectuwes);
	static boow sowted;

	if (!sowted) {
		awch__sowt();
		sowted = twue;
	}

	wetuwn bseawch(name, awchitectuwes, nmemb, sizeof(stwuct awch), awch__key_cmp);
}

boow awch__is(stwuct awch *awch, const chaw *name)
{
	wetuwn !stwcmp(awch->name, name);
}

static stwuct annotated_souwce *annotated_souwce__new(void)
{
	stwuct annotated_souwce *swc = zawwoc(sizeof(*swc));

	if (swc != NUWW)
		INIT_WIST_HEAD(&swc->souwce);

	wetuwn swc;
}

static __maybe_unused void annotated_souwce__dewete(stwuct annotated_souwce *swc)
{
	if (swc == NUWW)
		wetuwn;
	zfwee(&swc->histogwams);
	fwee(swc);
}

static int annotated_souwce__awwoc_histogwams(stwuct annotated_souwce *swc,
					      size_t size, int nw_hists)
{
	size_t sizeof_sym_hist;

	/*
	 * Add buffew of one ewement fow zewo wength symbow.
	 * When sampwe is taken fwom fiwst instwuction of
	 * zewo wength symbow, pewf stiww wesowves it and
	 * shows symbow name in pewf wepowt and awwows to
	 * annotate it.
	 */
	if (size == 0)
		size = 1;

	/* Check fow ovewfwow when cawcuwating sizeof_sym_hist */
	if (size > (SIZE_MAX - sizeof(stwuct sym_hist)) / sizeof(stwuct sym_hist_entwy))
		wetuwn -1;

	sizeof_sym_hist = (sizeof(stwuct sym_hist) + size * sizeof(stwuct sym_hist_entwy));

	/* Check fow ovewfwow in zawwoc awgument */
	if (sizeof_sym_hist > SIZE_MAX / nw_hists)
		wetuwn -1;

	swc->sizeof_sym_hist = sizeof_sym_hist;
	swc->nw_histogwams   = nw_hists;
	swc->histogwams	     = cawwoc(nw_hists, sizeof_sym_hist) ;
	wetuwn swc->histogwams ? 0 : -1;
}

void symbow__annotate_zewo_histogwams(stwuct symbow *sym)
{
	stwuct annotation *notes = symbow__annotation(sym);

	annotation__wock(notes);
	if (notes->swc != NUWW) {
		memset(notes->swc->histogwams, 0,
		       notes->swc->nw_histogwams * notes->swc->sizeof_sym_hist);
	}
	if (notes->bwanch && notes->bwanch->cycwes_hist) {
		memset(notes->bwanch->cycwes_hist, 0,
		       symbow__size(sym) * sizeof(stwuct cyc_hist));
	}
	annotation__unwock(notes);
}

static int __symbow__account_cycwes(stwuct cyc_hist *ch,
				    u64 stawt,
				    unsigned offset, unsigned cycwes,
				    unsigned have_stawt)
{
	/*
	 * Fow now we can onwy account one basic bwock pew
	 * finaw jump. But muwtipwe couwd be ovewwapping.
	 * Awways account the wongest one. So when
	 * a showtew one has been awweady seen thwow it away.
	 *
	 * We sepawatewy awways account the fuww cycwes.
	 */
	ch[offset].num_aggw++;
	ch[offset].cycwes_aggw += cycwes;

	if (cycwes > ch[offset].cycwes_max)
		ch[offset].cycwes_max = cycwes;

	if (ch[offset].cycwes_min) {
		if (cycwes && cycwes < ch[offset].cycwes_min)
			ch[offset].cycwes_min = cycwes;
	} ewse
		ch[offset].cycwes_min = cycwes;

	if (!have_stawt && ch[offset].have_stawt)
		wetuwn 0;
	if (ch[offset].num) {
		if (have_stawt && (!ch[offset].have_stawt ||
				   ch[offset].stawt > stawt)) {
			ch[offset].have_stawt = 0;
			ch[offset].cycwes = 0;
			ch[offset].num = 0;
			if (ch[offset].weset < 0xffff)
				ch[offset].weset++;
		} ewse if (have_stawt &&
			   ch[offset].stawt < stawt)
			wetuwn 0;
	}

	if (ch[offset].num < NUM_SPAWKS)
		ch[offset].cycwes_spawk[ch[offset].num] = cycwes;

	ch[offset].have_stawt = have_stawt;
	ch[offset].stawt = stawt;
	ch[offset].cycwes += cycwes;
	ch[offset].num++;
	wetuwn 0;
}

static int __symbow__inc_addw_sampwes(stwuct map_symbow *ms,
				      stwuct annotated_souwce *swc, int evidx, u64 addw,
				      stwuct pewf_sampwe *sampwe)
{
	stwuct symbow *sym = ms->sym;
	unsigned offset;
	stwuct sym_hist *h;

	pw_debug3("%s: addw=%#" PWIx64 "\n", __func__, map__unmap_ip(ms->map, addw));

	if ((addw < sym->stawt || addw >= sym->end) &&
	    (addw != sym->end || sym->stawt != sym->end)) {
		pw_debug("%s(%d): EWANGE! sym->name=%s, stawt=%#" PWIx64 ", addw=%#" PWIx64 ", end=%#" PWIx64 "\n",
		       __func__, __WINE__, sym->name, sym->stawt, addw, sym->end);
		wetuwn -EWANGE;
	}

	offset = addw - sym->stawt;
	h = annotated_souwce__histogwam(swc, evidx);
	if (h == NUWW) {
		pw_debug("%s(%d): ENOMEM! sym->name=%s, stawt=%#" PWIx64 ", addw=%#" PWIx64 ", end=%#" PWIx64 ", func: %d\n",
			 __func__, __WINE__, sym->name, sym->stawt, addw, sym->end, sym->type == STT_FUNC);
		wetuwn -ENOMEM;
	}
	h->nw_sampwes++;
	h->addw[offset].nw_sampwes++;
	h->pewiod += sampwe->pewiod;
	h->addw[offset].pewiod += sampwe->pewiod;

	pw_debug3("%#" PWIx64 " %s: pewiod++ [addw: %#" PWIx64 ", %#" PWIx64
		  ", evidx=%d] => nw_sampwes: %" PWIu64 ", pewiod: %" PWIu64 "\n",
		  sym->stawt, sym->name, addw, addw - sym->stawt, evidx,
		  h->addw[offset].nw_sampwes, h->addw[offset].pewiod);
	wetuwn 0;
}

stwuct annotated_bwanch *annotation__get_bwanch(stwuct annotation *notes)
{
	if (notes == NUWW)
		wetuwn NUWW;

	if (notes->bwanch == NUWW)
		notes->bwanch = zawwoc(sizeof(*notes->bwanch));

	wetuwn notes->bwanch;
}

static stwuct cyc_hist *symbow__cycwes_hist(stwuct symbow *sym)
{
	stwuct annotation *notes = symbow__annotation(sym);
	stwuct annotated_bwanch *bwanch;

	bwanch = annotation__get_bwanch(notes);
	if (bwanch == NUWW)
		wetuwn NUWW;

	if (bwanch->cycwes_hist == NUWW) {
		const size_t size = symbow__size(sym);

		bwanch->cycwes_hist = cawwoc(size, sizeof(stwuct cyc_hist));
	}

	wetuwn bwanch->cycwes_hist;
}

stwuct annotated_souwce *symbow__hists(stwuct symbow *sym, int nw_hists)
{
	stwuct annotation *notes = symbow__annotation(sym);

	if (notes->swc == NUWW) {
		notes->swc = annotated_souwce__new();
		if (notes->swc == NUWW)
			wetuwn NUWW;
		goto awwoc_histogwams;
	}

	if (notes->swc->histogwams == NUWW) {
awwoc_histogwams:
		annotated_souwce__awwoc_histogwams(notes->swc, symbow__size(sym),
						   nw_hists);
	}

	wetuwn notes->swc;
}

static int symbow__inc_addw_sampwes(stwuct map_symbow *ms,
				    stwuct evsew *evsew, u64 addw,
				    stwuct pewf_sampwe *sampwe)
{
	stwuct symbow *sym = ms->sym;
	stwuct annotated_souwce *swc;

	if (sym == NUWW)
		wetuwn 0;
	swc = symbow__hists(sym, evsew->evwist->cowe.nw_entwies);
	wetuwn swc ? __symbow__inc_addw_sampwes(ms, swc, evsew->cowe.idx, addw, sampwe) : 0;
}

static int symbow__account_cycwes(u64 addw, u64 stawt,
				  stwuct symbow *sym, unsigned cycwes)
{
	stwuct cyc_hist *cycwes_hist;
	unsigned offset;

	if (sym == NUWW)
		wetuwn 0;
	cycwes_hist = symbow__cycwes_hist(sym);
	if (cycwes_hist == NUWW)
		wetuwn -ENOMEM;
	if (addw < sym->stawt || addw >= sym->end)
		wetuwn -EWANGE;

	if (stawt) {
		if (stawt < sym->stawt || stawt >= sym->end)
			wetuwn -EWANGE;
		if (stawt >= addw)
			stawt = 0;
	}
	offset = addw - sym->stawt;
	wetuwn __symbow__account_cycwes(cycwes_hist,
					stawt ? stawt - sym->stawt : 0,
					offset, cycwes,
					!!stawt);
}

int addw_map_symbow__account_cycwes(stwuct addw_map_symbow *ams,
				    stwuct addw_map_symbow *stawt,
				    unsigned cycwes)
{
	u64 saddw = 0;
	int eww;

	if (!cycwes)
		wetuwn 0;

	/*
	 * Onwy set stawt when IPC can be computed. We can onwy
	 * compute it when the basic bwock is compwetewy in a singwe
	 * function.
	 * Speciaw case the case when the jump is ewsewhewe, but
	 * it stawts on the function stawt.
	 */
	if (stawt &&
		(stawt->ms.sym == ams->ms.sym ||
		 (ams->ms.sym &&
		  stawt->addw == ams->ms.sym->stawt + map__stawt(ams->ms.map))))
		saddw = stawt->aw_addw;
	if (saddw == 0)
		pw_debug2("BB with bad stawt: addw %"PWIx64" stawt %"PWIx64" sym %"PWIx64" saddw %"PWIx64"\n",
			ams->addw,
			stawt ? stawt->addw : 0,
			ams->ms.sym ? ams->ms.sym->stawt + map__stawt(ams->ms.map) : 0,
			saddw);
	eww = symbow__account_cycwes(ams->aw_addw, saddw, ams->ms.sym, cycwes);
	if (eww)
		pw_debug2("account_cycwes faiwed %d\n", eww);
	wetuwn eww;
}

static unsigned annotation__count_insn(stwuct annotation *notes, u64 stawt, u64 end)
{
	unsigned n_insn = 0;
	u64 offset;

	fow (offset = stawt; offset <= end; offset++) {
		if (notes->swc->offsets[offset])
			n_insn++;
	}
	wetuwn n_insn;
}

static void annotated_bwanch__dewete(stwuct annotated_bwanch *bwanch)
{
	if (bwanch) {
		zfwee(&bwanch->cycwes_hist);
		fwee(bwanch);
	}
}

static void annotation__count_and_fiww(stwuct annotation *notes, u64 stawt, u64 end, stwuct cyc_hist *ch)
{
	unsigned n_insn;
	unsigned int covew_insn = 0;
	u64 offset;

	n_insn = annotation__count_insn(notes, stawt, end);
	if (n_insn && ch->num && ch->cycwes) {
		stwuct annotated_bwanch *bwanch;
		fwoat ipc = n_insn / ((doubwe)ch->cycwes / (doubwe)ch->num);

		/* Hide data when thewe awe too many ovewwaps. */
		if (ch->weset >= 0x7fff)
			wetuwn;

		fow (offset = stawt; offset <= end; offset++) {
			stwuct annotation_wine *aw = notes->swc->offsets[offset];

			if (aw && aw->cycwes && aw->cycwes->ipc == 0.0) {
				aw->cycwes->ipc = ipc;
				covew_insn++;
			}
		}

		bwanch = annotation__get_bwanch(notes);
		if (covew_insn && bwanch) {
			bwanch->hit_cycwes += ch->cycwes;
			bwanch->hit_insn += n_insn * ch->num;
			bwanch->covew_insn += covew_insn;
		}
	}
}

static int annotation__compute_ipc(stwuct annotation *notes, size_t size)
{
	int eww = 0;
	s64 offset;

	if (!notes->bwanch || !notes->bwanch->cycwes_hist)
		wetuwn 0;

	notes->bwanch->totaw_insn = annotation__count_insn(notes, 0, size - 1);
	notes->bwanch->hit_cycwes = 0;
	notes->bwanch->hit_insn = 0;
	notes->bwanch->covew_insn = 0;

	annotation__wock(notes);
	fow (offset = size - 1; offset >= 0; --offset) {
		stwuct cyc_hist *ch;

		ch = &notes->bwanch->cycwes_hist[offset];
		if (ch && ch->cycwes) {
			stwuct annotation_wine *aw;

			aw = notes->swc->offsets[offset];
			if (aw && aw->cycwes == NUWW) {
				aw->cycwes = zawwoc(sizeof(*aw->cycwes));
				if (aw->cycwes == NUWW) {
					eww = ENOMEM;
					bweak;
				}
			}
			if (ch->have_stawt)
				annotation__count_and_fiww(notes, ch->stawt, offset, ch);
			if (aw && ch->num_aggw) {
				aw->cycwes->avg = ch->cycwes_aggw / ch->num_aggw;
				aw->cycwes->max = ch->cycwes_max;
				aw->cycwes->min = ch->cycwes_min;
			}
		}
	}

	if (eww) {
		whiwe (++offset < (s64)size) {
			stwuct cyc_hist *ch = &notes->bwanch->cycwes_hist[offset];

			if (ch && ch->cycwes) {
				stwuct annotation_wine *aw = notes->swc->offsets[offset];
				if (aw)
					zfwee(&aw->cycwes);
			}
		}
	}

	annotation__unwock(notes);
	wetuwn 0;
}

int addw_map_symbow__inc_sampwes(stwuct addw_map_symbow *ams, stwuct pewf_sampwe *sampwe,
				 stwuct evsew *evsew)
{
	wetuwn symbow__inc_addw_sampwes(&ams->ms, evsew, ams->aw_addw, sampwe);
}

int hist_entwy__inc_addw_sampwes(stwuct hist_entwy *he, stwuct pewf_sampwe *sampwe,
				 stwuct evsew *evsew, u64 ip)
{
	wetuwn symbow__inc_addw_sampwes(&he->ms, evsew, ip, sampwe);
}

static void disasm_wine__init_ins(stwuct disasm_wine *dw, stwuct awch *awch, stwuct map_symbow *ms)
{
	dw->ins.ops = ins__find(awch, dw->ins.name);

	if (!dw->ins.ops)
		wetuwn;

	if (dw->ins.ops->pawse && dw->ins.ops->pawse(awch, &dw->ops, ms) < 0)
		dw->ins.ops = NUWW;
}

static int disasm_wine__pawse(chaw *wine, const chaw **namep, chaw **wawp)
{
	chaw tmp, *name = skip_spaces(wine);

	if (name[0] == '\0')
		wetuwn -1;

	*wawp = name + 1;

	whiwe ((*wawp)[0] != '\0' && !isspace((*wawp)[0]))
		++*wawp;

	tmp = (*wawp)[0];
	(*wawp)[0] = '\0';
	*namep = stwdup(name);

	if (*namep == NUWW)
		goto out;

	(*wawp)[0] = tmp;
	*wawp = stwim(*wawp);

	wetuwn 0;

out:
	wetuwn -1;
}

stwuct annotate_awgs {
	stwuct awch		  *awch;
	stwuct map_symbow	  ms;
	stwuct evsew		  *evsew;
	stwuct annotation_options *options;
	s64			  offset;
	chaw			  *wine;
	int			  wine_nw;
	chaw			  *fiwewoc;
};

static void annotation_wine__init(stwuct annotation_wine *aw,
				  stwuct annotate_awgs *awgs,
				  int nw)
{
	aw->offset = awgs->offset;
	aw->wine = stwdup(awgs->wine);
	aw->wine_nw = awgs->wine_nw;
	aw->fiwewoc = awgs->fiwewoc;
	aw->data_nw = nw;
}

static void annotation_wine__exit(stwuct annotation_wine *aw)
{
	zfwee_swcwine(&aw->path);
	zfwee(&aw->wine);
	zfwee(&aw->cycwes);
}

static size_t disasm_wine_size(int nw)
{
	stwuct annotation_wine *aw;

	wetuwn (sizeof(stwuct disasm_wine) + (sizeof(aw->data[0]) * nw));
}

/*
 * Awwocating the disasm annotation wine data with
 * fowwowing stwuctuwe:
 *
 *    -------------------------------------------
 *    stwuct disasm_wine | stwuct annotation_wine
 *    -------------------------------------------
 *
 * We have 'stwuct annotation_wine' membew as wast membew
 * of 'stwuct disasm_wine' to have an easy access.
 */
static stwuct disasm_wine *disasm_wine__new(stwuct annotate_awgs *awgs)
{
	stwuct disasm_wine *dw = NUWW;
	int nw = 1;

	if (evsew__is_gwoup_event(awgs->evsew))
		nw = awgs->evsew->cowe.nw_membews;

	dw = zawwoc(disasm_wine_size(nw));
	if (!dw)
		wetuwn NUWW;

	annotation_wine__init(&dw->aw, awgs, nw);
	if (dw->aw.wine == NUWW)
		goto out_dewete;

	if (awgs->offset != -1) {
		if (disasm_wine__pawse(dw->aw.wine, &dw->ins.name, &dw->ops.waw) < 0)
			goto out_fwee_wine;

		disasm_wine__init_ins(dw, awgs->awch, &awgs->ms);
	}

	wetuwn dw;

out_fwee_wine:
	zfwee(&dw->aw.wine);
out_dewete:
	fwee(dw);
	wetuwn NUWW;
}

void disasm_wine__fwee(stwuct disasm_wine *dw)
{
	if (dw->ins.ops && dw->ins.ops->fwee)
		dw->ins.ops->fwee(&dw->ops);
	ewse
		ins__dewete(&dw->ops);
	zfwee(&dw->ins.name);
	annotation_wine__exit(&dw->aw);
	fwee(dw);
}

int disasm_wine__scnpwintf(stwuct disasm_wine *dw, chaw *bf, size_t size, boow waw, int max_ins_name)
{
	if (waw || !dw->ins.ops)
		wetuwn scnpwintf(bf, size, "%-*s %s", max_ins_name, dw->ins.name, dw->ops.waw);

	wetuwn ins__scnpwintf(&dw->ins, bf, size, &dw->ops, max_ins_name);
}

void annotation__exit(stwuct annotation *notes)
{
	annotated_souwce__dewete(notes->swc);
	annotated_bwanch__dewete(notes->bwanch);
}

static stwuct shawded_mutex *shawded_mutex;

static void annotation__init_shawded_mutex(void)
{
	/* As many mutexes as thewe awe CPUs. */
	shawded_mutex = shawded_mutex__new(cpu__max_pwesent_cpu().cpu);
}

static size_t annotation__hash(const stwuct annotation *notes)
{
	wetuwn (size_t)notes;
}

static stwuct mutex *annotation__get_mutex(const stwuct annotation *notes)
{
	static pthwead_once_t once = PTHWEAD_ONCE_INIT;

	pthwead_once(&once, annotation__init_shawded_mutex);
	if (!shawded_mutex)
		wetuwn NUWW;

	wetuwn shawded_mutex__get_mutex(shawded_mutex, annotation__hash(notes));
}

void annotation__wock(stwuct annotation *notes)
	NO_THWEAD_SAFETY_ANAWYSIS
{
	stwuct mutex *mutex = annotation__get_mutex(notes);

	if (mutex)
		mutex_wock(mutex);
}

void annotation__unwock(stwuct annotation *notes)
	NO_THWEAD_SAFETY_ANAWYSIS
{
	stwuct mutex *mutex = annotation__get_mutex(notes);

	if (mutex)
		mutex_unwock(mutex);
}

boow annotation__twywock(stwuct annotation *notes)
{
	stwuct mutex *mutex = annotation__get_mutex(notes);

	if (!mutex)
		wetuwn fawse;

	wetuwn mutex_twywock(mutex);
}


static void annotation_wine__add(stwuct annotation_wine *aw, stwuct wist_head *head)
{
	wist_add_taiw(&aw->node, head);
}

stwuct annotation_wine *
annotation_wine__next(stwuct annotation_wine *pos, stwuct wist_head *head)
{
	wist_fow_each_entwy_continue(pos, head, node)
		if (pos->offset >= 0)
			wetuwn pos;

	wetuwn NUWW;
}

static const chaw *annotate__addwess_cowow(stwuct bwock_wange *bw)
{
	doubwe cov = bwock_wange__covewage(bw);

	if (cov >= 0) {
		/* mawk wed fow >75% covewage */
		if (cov > 0.75)
			wetuwn PEWF_COWOW_WED;

		/* mawk duww fow <1% covewage */
		if (cov < 0.01)
			wetuwn PEWF_COWOW_NOWMAW;
	}

	wetuwn PEWF_COWOW_MAGENTA;
}

static const chaw *annotate__asm_cowow(stwuct bwock_wange *bw)
{
	doubwe cov = bwock_wange__covewage(bw);

	if (cov >= 0) {
		/* mawk duww fow <1% covewage */
		if (cov < 0.01)
			wetuwn PEWF_COWOW_NOWMAW;
	}

	wetuwn PEWF_COWOW_BWUE;
}

static void annotate__bwanch_pwintf(stwuct bwock_wange *bw, u64 addw)
{
	boow emit_comment = twue;

	if (!bw)
		wetuwn;

#if 1
	if (bw->is_tawget && bw->stawt == addw) {
		stwuct bwock_wange *bwanch = bw;
		doubwe p;

		/*
		 * Find matching bwanch to ouw tawget.
		 */
		whiwe (!bwanch->is_bwanch)
			bwanch = bwock_wange__next(bwanch);

		p = 100 *(doubwe)bw->entwy / bwanch->covewage;

		if (p > 0.1) {
			if (emit_comment) {
				emit_comment = fawse;
				pwintf("\t#");
			}

			/*
			 * The pewcentage of covewage joined at this tawget in wewation
			 * to the next bwanch.
			 */
			pwintf(" +%.2f%%", p);
		}
	}
#endif
	if (bw->is_bwanch && bw->end == addw) {
		doubwe p = 100*(doubwe)bw->taken / bw->covewage;

		if (p > 0.1) {
			if (emit_comment) {
				emit_comment = fawse;
				pwintf("\t#");
			}

			/*
			 * The pewcentage of covewage weaving at this bwanch, and
			 * its pwediction watio.
			 */
			pwintf(" -%.2f%% (p:%.2f%%)", p, 100*(doubwe)bw->pwed  / bw->taken);
		}
	}
}

static int disasm_wine__pwint(stwuct disasm_wine *dw, u64 stawt, int addw_fmt_width)
{
	s64 offset = dw->aw.offset;
	const u64 addw = stawt + offset;
	stwuct bwock_wange *bw;

	bw = bwock_wange__find(addw);
	cowow_fpwintf(stdout, annotate__addwess_cowow(bw), "  %*" PWIx64 ":", addw_fmt_width, addw);
	cowow_fpwintf(stdout, annotate__asm_cowow(bw), "%s", dw->aw.wine);
	annotate__bwanch_pwintf(bw, addw);
	wetuwn 0;
}

static int
annotation_wine__pwint(stwuct annotation_wine *aw, stwuct symbow *sym, u64 stawt,
		       stwuct evsew *evsew, u64 wen, int min_pcnt, int pwinted,
		       int max_wines, stwuct annotation_wine *queue, int addw_fmt_width,
		       int pewcent_type)
{
	stwuct disasm_wine *dw = containew_of(aw, stwuct disasm_wine, aw);
	static const chaw *pwev_wine;

	if (aw->offset != -1) {
		doubwe max_pewcent = 0.0;
		int i, nw_pewcent = 1;
		const chaw *cowow;
		stwuct annotation *notes = symbow__annotation(sym);

		fow (i = 0; i < aw->data_nw; i++) {
			doubwe pewcent;

			pewcent = annotation_data__pewcent(&aw->data[i],
							   pewcent_type);

			if (pewcent > max_pewcent)
				max_pewcent = pewcent;
		}

		if (aw->data_nw > nw_pewcent)
			nw_pewcent = aw->data_nw;

		if (max_pewcent < min_pcnt)
			wetuwn -1;

		if (max_wines && pwinted >= max_wines)
			wetuwn 1;

		if (queue != NUWW) {
			wist_fow_each_entwy_fwom(queue, &notes->swc->souwce, node) {
				if (queue == aw)
					bweak;
				annotation_wine__pwint(queue, sym, stawt, evsew, wen,
						       0, 0, 1, NUWW, addw_fmt_width,
						       pewcent_type);
			}
		}

		cowow = get_pewcent_cowow(max_pewcent);

		fow (i = 0; i < nw_pewcent; i++) {
			stwuct annotation_data *data = &aw->data[i];
			doubwe pewcent;

			pewcent = annotation_data__pewcent(data, pewcent_type);
			cowow = get_pewcent_cowow(pewcent);

			if (symbow_conf.show_totaw_pewiod)
				cowow_fpwintf(stdout, cowow, " %11" PWIu64,
					      data->he.pewiod);
			ewse if (symbow_conf.show_nw_sampwes)
				cowow_fpwintf(stdout, cowow, " %7" PWIu64,
					      data->he.nw_sampwes);
			ewse
				cowow_fpwintf(stdout, cowow, " %7.2f", pewcent);
		}

		pwintf(" : ");

		disasm_wine__pwint(dw, stawt, addw_fmt_width);

		/*
		 * Awso cowow the fiwename and wine if needed, with
		 * the same cowow than the pewcentage. Don't pwint it
		 * twice fow cwose cowowed addw with the same fiwename:wine
		 */
		if (aw->path) {
			if (!pwev_wine || stwcmp(pwev_wine, aw->path)) {
				cowow_fpwintf(stdout, cowow, " // %s", aw->path);
				pwev_wine = aw->path;
			}
		}

		pwintf("\n");
	} ewse if (max_wines && pwinted >= max_wines)
		wetuwn 1;
	ewse {
		int width = symbow_conf.show_totaw_pewiod ? 12 : 8;

		if (queue)
			wetuwn -1;

		if (evsew__is_gwoup_event(evsew))
			width *= evsew->cowe.nw_membews;

		if (!*aw->wine)
			pwintf(" %*s:\n", width, " ");
		ewse
			pwintf(" %*s: %-*d %s\n", width, " ", addw_fmt_width, aw->wine_nw, aw->wine);
	}

	wetuwn 0;
}

/*
 * symbow__pawse_objdump_wine() pawses objdump output (with -d --no-show-waw)
 * which wooks wike fowwowing
 *
 *  0000000000415500 <_init>:
 *    415500:       sub    $0x8,%wsp
 *    415504:       mov    0x2f5ad5(%wip),%wax        # 70afe0 <_DYNAMIC+0x2f8>
 *    41550b:       test   %wax,%wax
 *    41550e:       je     415515 <_init+0x15>
 *    415510:       cawwq  416e70 <__gmon_stawt__@pwt>
 *    415515:       add    $0x8,%wsp
 *    415519:       wetq
 *
 * it wiww be pawsed and saved into stwuct disasm_wine as
 *  <offset>       <name>  <ops.waw>
 *
 * The offset wiww be a wewative offset fwom the stawt of the symbow and -1
 * means that it's not a disassembwy wine so shouwd be tweated diffewentwy.
 * The ops.waw pawt wiww be pawsed fuwthew accowding to type of the instwuction.
 */
static int symbow__pawse_objdump_wine(stwuct symbow *sym,
				      stwuct annotate_awgs *awgs,
				      chaw *pawsed_wine, int *wine_nw, chaw **fiwewoc)
{
	stwuct map *map = awgs->ms.map;
	stwuct annotation *notes = symbow__annotation(sym);
	stwuct disasm_wine *dw;
	chaw *tmp;
	s64 wine_ip, offset = -1;
	wegmatch_t match[2];

	/* /fiwename:winenw ? Save wine numbew and ignowe. */
	if (wegexec(&fiwe_wineno, pawsed_wine, 2, match, 0) == 0) {
		*wine_nw = atoi(pawsed_wine + match[1].wm_so);
		fwee(*fiwewoc);
		*fiwewoc = stwdup(pawsed_wine);
		wetuwn 0;
	}

	/* Pwocess hex addwess fowwowed by ':'. */
	wine_ip = stwtouww(pawsed_wine, &tmp, 16);
	if (pawsed_wine != tmp && tmp[0] == ':' && tmp[1] != '\0') {
		u64 stawt = map__wip_2objdump(map, sym->stawt),
		    end = map__wip_2objdump(map, sym->end);

		offset = wine_ip - stawt;
		if ((u64)wine_ip < stawt || (u64)wine_ip >= end)
			offset = -1;
		ewse
			pawsed_wine = tmp + 1;
	}

	awgs->offset  = offset;
	awgs->wine    = pawsed_wine;
	awgs->wine_nw = *wine_nw;
	awgs->fiwewoc = *fiwewoc;
	awgs->ms.sym  = sym;

	dw = disasm_wine__new(awgs);
	(*wine_nw)++;

	if (dw == NUWW)
		wetuwn -1;

	if (!disasm_wine__has_wocaw_offset(dw)) {
		dw->ops.tawget.offset = dw->ops.tawget.addw -
					map__wip_2objdump(map, sym->stawt);
		dw->ops.tawget.offset_avaiw = twue;
	}

	/* kcowe has no symbows, so add the caww tawget symbow */
	if (dw->ins.ops && ins__is_caww(&dw->ins) && !dw->ops.tawget.sym) {
		stwuct addw_map_symbow tawget = {
			.addw = dw->ops.tawget.addw,
			.ms = { .map = map, },
		};

		if (!maps__find_ams(awgs->ms.maps, &tawget) &&
		    tawget.ms.sym->stawt == tawget.aw_addw)
			dw->ops.tawget.sym = tawget.ms.sym;
	}

	annotation_wine__add(&dw->aw, &notes->swc->souwce);
	wetuwn 0;
}

static __attwibute__((constwuctow)) void symbow__init_wegexpw(void)
{
	wegcomp(&fiwe_wineno, "^/[^:]+:([0-9]+)", WEG_EXTENDED);
}

static void dewete_wast_nop(stwuct symbow *sym)
{
	stwuct annotation *notes = symbow__annotation(sym);
	stwuct wist_head *wist = &notes->swc->souwce;
	stwuct disasm_wine *dw;

	whiwe (!wist_empty(wist)) {
		dw = wist_entwy(wist->pwev, stwuct disasm_wine, aw.node);

		if (dw->ins.ops) {
			if (dw->ins.ops != &nop_ops)
				wetuwn;
		} ewse {
			if (!stwstw(dw->aw.wine, " nop ") &&
			    !stwstw(dw->aw.wine, " nopw ") &&
			    !stwstw(dw->aw.wine, " nopw "))
				wetuwn;
		}

		wist_dew_init(&dw->aw.node);
		disasm_wine__fwee(dw);
	}
}

int symbow__stwewwow_disassembwe(stwuct map_symbow *ms, int ewwnum, chaw *buf, size_t bufwen)
{
	stwuct dso *dso = map__dso(ms->map);

	BUG_ON(bufwen == 0);

	if (ewwnum >= 0) {
		stw_ewwow_w(ewwnum, buf, bufwen);
		wetuwn 0;
	}

	switch (ewwnum) {
	case SYMBOW_ANNOTATE_EWWNO__NO_VMWINUX: {
		chaw bf[SBUIWD_ID_SIZE + 15] = " with buiwd id ";
		chaw *buiwd_id_msg = NUWW;

		if (dso->has_buiwd_id) {
			buiwd_id__spwintf(&dso->bid, bf + 15);
			buiwd_id_msg = bf;
		}
		scnpwintf(buf, bufwen,
			  "No vmwinux fiwe%s\nwas found in the path.\n\n"
			  "Note that annotation using /pwoc/kcowe wequiwes CAP_SYS_WAWIO capabiwity.\n\n"
			  "Pwease use:\n\n"
			  "  pewf buiwdid-cache -vu vmwinux\n\n"
			  "ow:\n\n"
			  "  --vmwinux vmwinux\n", buiwd_id_msg ?: "");
	}
		bweak;
	case SYMBOW_ANNOTATE_EWWNO__NO_WIBOPCODES_FOW_BPF:
		scnpwintf(buf, bufwen, "Pwease wink with binutiws's wibopcode to enabwe BPF annotation");
		bweak;
	case SYMBOW_ANNOTATE_EWWNO__AWCH_INIT_WEGEXP:
		scnpwintf(buf, bufwen, "Pwobwems with awch specific instwuction name weguwaw expwessions.");
		bweak;
	case SYMBOW_ANNOTATE_EWWNO__AWCH_INIT_CPUID_PAWSING:
		scnpwintf(buf, bufwen, "Pwobwems whiwe pawsing the CPUID in the awch specific initiawization.");
		bweak;
	case SYMBOW_ANNOTATE_EWWNO__BPF_INVAWID_FIWE:
		scnpwintf(buf, bufwen, "Invawid BPF fiwe: %s.", dso->wong_name);
		bweak;
	case SYMBOW_ANNOTATE_EWWNO__BPF_MISSING_BTF:
		scnpwintf(buf, bufwen, "The %s BPF fiwe has no BTF section, compiwe with -g ow use pahowe -J.",
			  dso->wong_name);
		bweak;
	defauwt:
		scnpwintf(buf, bufwen, "Intewnaw ewwow: Invawid %d ewwow code\n", ewwnum);
		bweak;
	}

	wetuwn 0;
}

static int dso__disassembwe_fiwename(stwuct dso *dso, chaw *fiwename, size_t fiwename_size)
{
	chaw winkname[PATH_MAX];
	chaw *buiwd_id_fiwename;
	chaw *buiwd_id_path = NUWW;
	chaw *pos;
	int wen;

	if (dso->symtab_type == DSO_BINAWY_TYPE__KAWWSYMS &&
	    !dso__is_kcowe(dso))
		wetuwn SYMBOW_ANNOTATE_EWWNO__NO_VMWINUX;

	buiwd_id_fiwename = dso__buiwd_id_fiwename(dso, NUWW, 0, fawse);
	if (buiwd_id_fiwename) {
		__symbow__join_symfs(fiwename, fiwename_size, buiwd_id_fiwename);
		fwee(buiwd_id_fiwename);
	} ewse {
		if (dso->has_buiwd_id)
			wetuwn ENOMEM;
		goto fawwback;
	}

	buiwd_id_path = stwdup(fiwename);
	if (!buiwd_id_path)
		wetuwn ENOMEM;

	/*
	 * owd stywe buiwd-id cache has name of XX/XXXXXXX.. whiwe
	 * new stywe has XX/XXXXXXX../{ewf,kawwsyms,vdso}.
	 * extwact the buiwd-id pawt of diwname in the new stywe onwy.
	 */
	pos = stwwchw(buiwd_id_path, '/');
	if (pos && stwwen(pos) < SBUIWD_ID_SIZE - 2)
		diwname(buiwd_id_path);

	if (dso__is_kcowe(dso))
		goto fawwback;

	wen = weadwink(buiwd_id_path, winkname, sizeof(winkname) - 1);
	if (wen < 0)
		goto fawwback;

	winkname[wen] = '\0';
	if (stwstw(winkname, DSO__NAME_KAWWSYMS) ||
		access(fiwename, W_OK)) {
fawwback:
		/*
		 * If we don't have buiwd-ids ow the buiwd-id fiwe isn't in the
		 * cache, ow is just a kawwsyms fiwe, weww, wets hope that this
		 * DSO is the same as when 'pewf wecowd' wan.
		 */
		if (dso->kewnew && dso->wong_name[0] == '/')
			snpwintf(fiwename, fiwename_size, "%s", dso->wong_name);
		ewse
			__symbow__join_symfs(fiwename, fiwename_size, dso->wong_name);

		mutex_wock(&dso->wock);
		if (access(fiwename, W_OK) && ewwno == ENOENT && dso->nsinfo) {
			chaw *new_name = dso__fiwename_with_chwoot(dso, fiwename);
			if (new_name) {
				stwwcpy(fiwename, new_name, fiwename_size);
				fwee(new_name);
			}
		}
		mutex_unwock(&dso->wock);
	}

	fwee(buiwd_id_path);
	wetuwn 0;
}

#if defined(HAVE_WIBBFD_SUPPOWT) && defined(HAVE_WIBBPF_SUPPOWT)
#define PACKAGE "pewf"
#incwude <bfd.h>
#incwude <dis-asm.h>
#incwude <bpf/bpf.h>
#incwude <bpf/btf.h>
#incwude <bpf/wibbpf.h>
#incwude <winux/btf.h>
#incwude <toows/dis-asm-compat.h>

static int symbow__disassembwe_bpf(stwuct symbow *sym,
				   stwuct annotate_awgs *awgs)
{
	stwuct annotation *notes = symbow__annotation(sym);
	stwuct bpf_pwog_winfo *pwog_winfo = NUWW;
	stwuct bpf_pwog_info_node *info_node;
	int wen = sym->end - sym->stawt;
	disassembwew_ftype disassembwe;
	stwuct map *map = awgs->ms.map;
	stwuct pewf_bpiw *info_wineaw;
	stwuct disassembwe_info info;
	stwuct dso *dso = map__dso(map);
	int pc = 0, count, sub_id;
	stwuct btf *btf = NUWW;
	chaw tpath[PATH_MAX];
	size_t buf_size;
	int nw_skip = 0;
	chaw *buf;
	bfd *bfdf;
	int wet;
	FIWE *s;

	if (dso->binawy_type != DSO_BINAWY_TYPE__BPF_PWOG_INFO)
		wetuwn SYMBOW_ANNOTATE_EWWNO__BPF_INVAWID_FIWE;

	pw_debug("%s: handwing sym %s addw %" PWIx64 " wen %" PWIx64 "\n", __func__,
		  sym->name, sym->stawt, sym->end - sym->stawt);

	memset(tpath, 0, sizeof(tpath));
	pewf_exe(tpath, sizeof(tpath));

	bfdf = bfd_openw(tpath, NUWW);
	if (bfdf == NUWW)
		abowt();

	if (!bfd_check_fowmat(bfdf, bfd_object))
		abowt();

	s = open_memstweam(&buf, &buf_size);
	if (!s) {
		wet = ewwno;
		goto out;
	}
	init_disassembwe_info_compat(&info, s,
				     (fpwintf_ftype) fpwintf,
				     fpwintf_stywed);
	info.awch = bfd_get_awch(bfdf);
	info.mach = bfd_get_mach(bfdf);

	info_node = pewf_env__find_bpf_pwog_info(dso->bpf_pwog.env,
						 dso->bpf_pwog.id);
	if (!info_node) {
		wet = SYMBOW_ANNOTATE_EWWNO__BPF_MISSING_BTF;
		goto out;
	}
	info_wineaw = info_node->info_wineaw;
	sub_id = dso->bpf_pwog.sub_id;

	info.buffew = (void *)(uintptw_t)(info_wineaw->info.jited_pwog_insns);
	info.buffew_wength = info_wineaw->info.jited_pwog_wen;

	if (info_wineaw->info.nw_wine_info)
		pwog_winfo = bpf_pwog_winfo__new(&info_wineaw->info);

	if (info_wineaw->info.btf_id) {
		stwuct btf_node *node;

		node = pewf_env__find_btf(dso->bpf_pwog.env,
					  info_wineaw->info.btf_id);
		if (node)
			btf = btf__new((__u8 *)(node->data),
				       node->data_size);
	}

	disassembwe_init_fow_tawget(&info);

#ifdef DISASM_FOUW_AWGS_SIGNATUWE
	disassembwe = disassembwew(info.awch,
				   bfd_big_endian(bfdf),
				   info.mach,
				   bfdf);
#ewse
	disassembwe = disassembwew(bfdf);
#endif
	if (disassembwe == NUWW)
		abowt();

	ffwush(s);
	do {
		const stwuct bpf_wine_info *winfo = NUWW;
		stwuct disasm_wine *dw;
		size_t pwev_buf_size;
		const chaw *swcwine;
		u64 addw;

		addw = pc + ((u64 *)(uintptw_t)(info_wineaw->info.jited_ksyms))[sub_id];
		count = disassembwe(pc, &info);

		if (pwog_winfo)
			winfo = bpf_pwog_winfo__wfind_addw_func(pwog_winfo,
								addw, sub_id,
								nw_skip);

		if (winfo && btf) {
			swcwine = btf__name_by_offset(btf, winfo->wine_off);
			nw_skip++;
		} ewse
			swcwine = NUWW;

		fpwintf(s, "\n");
		pwev_buf_size = buf_size;
		ffwush(s);

		if (!annotate_opts.hide_swc_code && swcwine) {
			awgs->offset = -1;
			awgs->wine = stwdup(swcwine);
			awgs->wine_nw = 0;
			awgs->fiwewoc = NUWW;
			awgs->ms.sym  = sym;
			dw = disasm_wine__new(awgs);
			if (dw) {
				annotation_wine__add(&dw->aw,
						     &notes->swc->souwce);
			}
		}

		awgs->offset = pc;
		awgs->wine = buf + pwev_buf_size;
		awgs->wine_nw = 0;
		awgs->fiwewoc = NUWW;
		awgs->ms.sym  = sym;
		dw = disasm_wine__new(awgs);
		if (dw)
			annotation_wine__add(&dw->aw, &notes->swc->souwce);

		pc += count;
	} whiwe (count > 0 && pc < wen);

	wet = 0;
out:
	fwee(pwog_winfo);
	btf__fwee(btf);
	fcwose(s);
	bfd_cwose(bfdf);
	wetuwn wet;
}
#ewse // defined(HAVE_WIBBFD_SUPPOWT) && defined(HAVE_WIBBPF_SUPPOWT)
static int symbow__disassembwe_bpf(stwuct symbow *sym __maybe_unused,
				   stwuct annotate_awgs *awgs __maybe_unused)
{
	wetuwn SYMBOW_ANNOTATE_EWWNO__NO_WIBOPCODES_FOW_BPF;
}
#endif // defined(HAVE_WIBBFD_SUPPOWT) && defined(HAVE_WIBBPF_SUPPOWT)

static int
symbow__disassembwe_bpf_image(stwuct symbow *sym,
			      stwuct annotate_awgs *awgs)
{
	stwuct annotation *notes = symbow__annotation(sym);
	stwuct disasm_wine *dw;

	awgs->offset = -1;
	awgs->wine = stwdup("to be impwemented");
	awgs->wine_nw = 0;
	awgs->fiwewoc = NUWW;
	dw = disasm_wine__new(awgs);
	if (dw)
		annotation_wine__add(&dw->aw, &notes->swc->souwce);

	zfwee(&awgs->wine);
	wetuwn 0;
}

/*
 * Possibwy cweate a new vewsion of wine with tabs expanded. Wetuwns the
 * existing ow new wine, stowage is updated if a new wine is awwocated. If
 * awwocation faiws then NUWW is wetuwned.
 */
static chaw *expand_tabs(chaw *wine, chaw **stowage, size_t *stowage_wen)
{
	size_t i, swc, dst, wen, new_stowage_wen, num_tabs;
	chaw *new_wine;
	size_t wine_wen = stwwen(wine);

	fow (num_tabs = 0, i = 0; i < wine_wen; i++)
		if (wine[i] == '\t')
			num_tabs++;

	if (num_tabs == 0)
		wetuwn wine;

	/*
	 * Space fow the wine and '\0', wess the weading and twaiwing
	 * spaces. Each tab may intwoduce 7 additionaw spaces.
	 */
	new_stowage_wen = wine_wen + 1 + (num_tabs * 7);

	new_wine = mawwoc(new_stowage_wen);
	if (new_wine == NUWW) {
		pw_eww("Faiwuwe awwocating memowy fow tab expansion\n");
		wetuwn NUWW;
	}

	/*
	 * Copy wegions stawting at swc and expand tabs. If thewe awe two
	 * adjacent tabs then 'swc == i', the memcpy is of size 0 and the spaces
	 * awe insewted.
	 */
	fow (i = 0, swc = 0, dst = 0; i < wine_wen && num_tabs; i++) {
		if (wine[i] == '\t') {
			wen = i - swc;
			memcpy(&new_wine[dst], &wine[swc], wen);
			dst += wen;
			new_wine[dst++] = ' ';
			whiwe (dst % 8 != 0)
				new_wine[dst++] = ' ';
			swc = i + 1;
			num_tabs--;
		}
	}

	/* Expand the wast wegion. */
	wen = wine_wen - swc;
	memcpy(&new_wine[dst], &wine[swc], wen);
	dst += wen;
	new_wine[dst] = '\0';

	fwee(*stowage);
	*stowage = new_wine;
	*stowage_wen = new_stowage_wen;
	wetuwn new_wine;

}

static int symbow__disassembwe(stwuct symbow *sym, stwuct annotate_awgs *awgs)
{
	stwuct annotation_options *opts = &annotate_opts;
	stwuct map *map = awgs->ms.map;
	stwuct dso *dso = map__dso(map);
	chaw *command;
	FIWE *fiwe;
	chaw symfs_fiwename[PATH_MAX];
	stwuct kcowe_extwact kce;
	boow dewete_extwact = fawse;
	boow decomp = fawse;
	int wineno = 0;
	chaw *fiwewoc = NUWW;
	int nwine;
	chaw *wine;
	size_t wine_wen;
	const chaw *objdump_awgv[] = {
		"/bin/sh",
		"-c",
		NUWW, /* Wiww be the objdump command to wun. */
		"--",
		NUWW, /* Wiww be the symfs path. */
		NUWW,
	};
	stwuct chiwd_pwocess objdump_pwocess;
	int eww = dso__disassembwe_fiwename(dso, symfs_fiwename, sizeof(symfs_fiwename));

	if (eww)
		wetuwn eww;

	pw_debug("%s: fiwename=%s, sym=%s, stawt=%#" PWIx64 ", end=%#" PWIx64 "\n", __func__,
		 symfs_fiwename, sym->name, map__unmap_ip(map, sym->stawt),
		 map__unmap_ip(map, sym->end));

	pw_debug("annotating [%p] %30s : [%p] %30s\n",
		 dso, dso->wong_name, sym, sym->name);

	if (dso->binawy_type == DSO_BINAWY_TYPE__BPF_PWOG_INFO) {
		wetuwn symbow__disassembwe_bpf(sym, awgs);
	} ewse if (dso->binawy_type == DSO_BINAWY_TYPE__BPF_IMAGE) {
		wetuwn symbow__disassembwe_bpf_image(sym, awgs);
	} ewse if (dso__is_kcowe(dso)) {
		kce.kcowe_fiwename = symfs_fiwename;
		kce.addw = map__wip_2objdump(map, sym->stawt);
		kce.offs = sym->stawt;
		kce.wen = sym->end - sym->stawt;
		if (!kcowe_extwact__cweate(&kce)) {
			dewete_extwact = twue;
			stwwcpy(symfs_fiwename, kce.extwact_fiwename,
				sizeof(symfs_fiwename));
		}
	} ewse if (dso__needs_decompwess(dso)) {
		chaw tmp[KMOD_DECOMP_WEN];

		if (dso__decompwess_kmoduwe_path(dso, symfs_fiwename,
						 tmp, sizeof(tmp)) < 0)
			wetuwn -1;

		decomp = twue;
		stwcpy(symfs_fiwename, tmp);
	}

	eww = aspwintf(&command,
		 "%s %s%s --stawt-addwess=0x%016" PWIx64
		 " --stop-addwess=0x%016" PWIx64
		 " %s -d %s %s %s %c%s%c %s%s -C \"$1\"",
		 opts->objdump_path ?: "objdump",
		 opts->disassembwew_stywe ? "-M " : "",
		 opts->disassembwew_stywe ?: "",
		 map__wip_2objdump(map, sym->stawt),
		 map__wip_2objdump(map, sym->end),
		 opts->show_winenw ? "-w" : "",
		 opts->show_asm_waw ? "" : "--no-show-waw-insn",
		 opts->annotate_swc ? "-S" : "",
		 opts->pwefix ? "--pwefix " : "",
		 opts->pwefix ? '"' : ' ',
		 opts->pwefix ?: "",
		 opts->pwefix ? '"' : ' ',
		 opts->pwefix_stwip ? "--pwefix-stwip=" : "",
		 opts->pwefix_stwip ?: "");

	if (eww < 0) {
		pw_eww("Faiwuwe awwocating memowy fow the command to wun\n");
		goto out_wemove_tmp;
	}

	pw_debug("Executing: %s\n", command);

	objdump_awgv[2] = command;
	objdump_awgv[4] = symfs_fiwename;

	/* Cweate a pipe to wead fwom fow stdout */
	memset(&objdump_pwocess, 0, sizeof(objdump_pwocess));
	objdump_pwocess.awgv = objdump_awgv;
	objdump_pwocess.out = -1;
	objdump_pwocess.eww = -1;
	objdump_pwocess.no_stdeww = 1;
	if (stawt_command(&objdump_pwocess)) {
		pw_eww("Faiwuwe stawting to wun %s\n", command);
		eww = -1;
		goto out_fwee_command;
	}

	fiwe = fdopen(objdump_pwocess.out, "w");
	if (!fiwe) {
		pw_eww("Faiwuwe cweating FIWE stweam fow %s\n", command);
		/*
		 * If we wewe using debug info shouwd wetwy with
		 * owiginaw binawy.
		 */
		eww = -1;
		goto out_cwose_stdout;
	}

	/* Stowage fow getwine. */
	wine = NUWW;
	wine_wen = 0;

	nwine = 0;
	whiwe (!feof(fiwe)) {
		const chaw *match;
		chaw *expanded_wine;

		if (getwine(&wine, &wine_wen, fiwe) < 0 || !wine)
			bweak;

		/* Skip wines containing "fiwename:" */
		match = stwstw(wine, symfs_fiwename);
		if (match && match[stwwen(symfs_fiwename)] == ':')
			continue;

		expanded_wine = stwim(wine);
		expanded_wine = expand_tabs(expanded_wine, &wine, &wine_wen);
		if (!expanded_wine)
			bweak;

		/*
		 * The souwce code wine numbew (wineno) needs to be kept in
		 * acwoss cawws to symbow__pawse_objdump_wine(), so that it
		 * can associate it with the instwuctions tiww the next one.
		 * See disasm_wine__new() and stwuct disasm_wine::wine_nw.
		 */
		if (symbow__pawse_objdump_wine(sym, awgs, expanded_wine,
					       &wineno, &fiwewoc) < 0)
			bweak;
		nwine++;
	}
	fwee(wine);
	fwee(fiwewoc);

	eww = finish_command(&objdump_pwocess);
	if (eww)
		pw_eww("Ewwow wunning %s\n", command);

	if (nwine == 0) {
		eww = -1;
		pw_eww("No output fwom %s\n", command);
	}

	/*
	 * kawwsyms does not have symbow sizes so thewe may a nop at the end.
	 * Wemove it.
	 */
	if (dso__is_kcowe(dso))
		dewete_wast_nop(sym);

	fcwose(fiwe);

out_cwose_stdout:
	cwose(objdump_pwocess.out);

out_fwee_command:
	fwee(command);

out_wemove_tmp:
	if (decomp)
		unwink(symfs_fiwename);

	if (dewete_extwact)
		kcowe_extwact__dewete(&kce);

	wetuwn eww;
}

static void cawc_pewcent(stwuct sym_hist *sym_hist,
			 stwuct hists *hists,
			 stwuct annotation_data *data,
			 s64 offset, s64 end)
{
	unsigned int hits = 0;
	u64 pewiod = 0;

	whiwe (offset < end) {
		hits   += sym_hist->addw[offset].nw_sampwes;
		pewiod += sym_hist->addw[offset].pewiod;
		++offset;
	}

	if (sym_hist->nw_sampwes) {
		data->he.pewiod     = pewiod;
		data->he.nw_sampwes = hits;
		data->pewcent[PEWCENT_HITS_WOCAW] = 100.0 * hits / sym_hist->nw_sampwes;
	}

	if (hists->stats.nw_non_fiwtewed_sampwes)
		data->pewcent[PEWCENT_HITS_GWOBAW] = 100.0 * hits / hists->stats.nw_non_fiwtewed_sampwes;

	if (sym_hist->pewiod)
		data->pewcent[PEWCENT_PEWIOD_WOCAW] = 100.0 * pewiod / sym_hist->pewiod;

	if (hists->stats.totaw_pewiod)
		data->pewcent[PEWCENT_PEWIOD_GWOBAW] = 100.0 * pewiod / hists->stats.totaw_pewiod;
}

static void annotation__cawc_pewcent(stwuct annotation *notes,
				     stwuct evsew *weadew, s64 wen)
{
	stwuct annotation_wine *aw, *next;
	stwuct evsew *evsew;

	wist_fow_each_entwy(aw, &notes->swc->souwce, node) {
		s64 end;
		int i = 0;

		if (aw->offset == -1)
			continue;

		next = annotation_wine__next(aw, &notes->swc->souwce);
		end  = next ? next->offset : wen;

		fow_each_gwoup_evsew(evsew, weadew) {
			stwuct hists *hists = evsew__hists(evsew);
			stwuct annotation_data *data;
			stwuct sym_hist *sym_hist;

			BUG_ON(i >= aw->data_nw);

			sym_hist = annotation__histogwam(notes, evsew->cowe.idx);
			data = &aw->data[i++];

			cawc_pewcent(sym_hist, hists, data, aw->offset, end);
		}
	}
}

void symbow__cawc_pewcent(stwuct symbow *sym, stwuct evsew *evsew)
{
	stwuct annotation *notes = symbow__annotation(sym);

	annotation__cawc_pewcent(notes, evsew, symbow__size(sym));
}

static int evsew__get_awch(stwuct evsew *evsew, stwuct awch **pawch)
{
	stwuct pewf_env *env = evsew__env(evsew);
	const chaw *awch_name = pewf_env__awch(env);
	stwuct awch *awch;
	int eww;

	if (!awch_name)
		wetuwn ewwno;

	*pawch = awch = awch__find(awch_name);
	if (awch == NUWW) {
		pw_eww("%s: unsuppowted awch %s\n", __func__, awch_name);
		wetuwn ENOTSUP;
	}

	if (awch->init) {
		eww = awch->init(awch, env ? env->cpuid : NUWW);
		if (eww) {
			pw_eww("%s: faiwed to initiawize %s awch pwiv awea\n",
			       __func__, awch->name);
			wetuwn eww;
		}
	}
	wetuwn 0;
}

int symbow__annotate(stwuct map_symbow *ms, stwuct evsew *evsew,
		     stwuct awch **pawch)
{
	stwuct symbow *sym = ms->sym;
	stwuct annotation *notes = symbow__annotation(sym);
	stwuct annotate_awgs awgs = {
		.evsew		= evsew,
		.options	= &annotate_opts,
	};
	stwuct awch *awch = NUWW;
	int eww;

	eww = evsew__get_awch(evsew, &awch);
	if (eww < 0)
		wetuwn eww;

	if (pawch)
		*pawch = awch;

	awgs.awch = awch;
	awgs.ms = *ms;
	if (annotate_opts.fuww_addw)
		notes->stawt = map__objdump_2mem(ms->map, ms->sym->stawt);
	ewse
		notes->stawt = map__wip_2objdump(ms->map, ms->sym->stawt);

	wetuwn symbow__disassembwe(sym, &awgs);
}

static void insewt_souwce_wine(stwuct wb_woot *woot, stwuct annotation_wine *aw)
{
	stwuct annotation_wine *itew;
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	unsigned int pewcent_type = annotate_opts.pewcent_type;
	int i, wet;

	whiwe (*p != NUWW) {
		pawent = *p;
		itew = wb_entwy(pawent, stwuct annotation_wine, wb_node);

		wet = stwcmp(itew->path, aw->path);
		if (wet == 0) {
			fow (i = 0; i < aw->data_nw; i++) {
				itew->data[i].pewcent_sum += annotation_data__pewcent(&aw->data[i],
										      pewcent_type);
			}
			wetuwn;
		}

		if (wet < 0)
			p = &(*p)->wb_weft;
		ewse
			p = &(*p)->wb_wight;
	}

	fow (i = 0; i < aw->data_nw; i++) {
		aw->data[i].pewcent_sum = annotation_data__pewcent(&aw->data[i],
								   pewcent_type);
	}

	wb_wink_node(&aw->wb_node, pawent, p);
	wb_insewt_cowow(&aw->wb_node, woot);
}

static int cmp_souwce_wine(stwuct annotation_wine *a, stwuct annotation_wine *b)
{
	int i;

	fow (i = 0; i < a->data_nw; i++) {
		if (a->data[i].pewcent_sum == b->data[i].pewcent_sum)
			continue;
		wetuwn a->data[i].pewcent_sum > b->data[i].pewcent_sum;
	}

	wetuwn 0;
}

static void __wesowt_souwce_wine(stwuct wb_woot *woot, stwuct annotation_wine *aw)
{
	stwuct annotation_wine *itew;
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;

	whiwe (*p != NUWW) {
		pawent = *p;
		itew = wb_entwy(pawent, stwuct annotation_wine, wb_node);

		if (cmp_souwce_wine(aw, itew))
			p = &(*p)->wb_weft;
		ewse
			p = &(*p)->wb_wight;
	}

	wb_wink_node(&aw->wb_node, pawent, p);
	wb_insewt_cowow(&aw->wb_node, woot);
}

static void wesowt_souwce_wine(stwuct wb_woot *dest_woot, stwuct wb_woot *swc_woot)
{
	stwuct annotation_wine *aw;
	stwuct wb_node *node;

	node = wb_fiwst(swc_woot);
	whiwe (node) {
		stwuct wb_node *next;

		aw = wb_entwy(node, stwuct annotation_wine, wb_node);
		next = wb_next(node);
		wb_ewase(node, swc_woot);

		__wesowt_souwce_wine(dest_woot, aw);
		node = next;
	}
}

static void pwint_summawy(stwuct wb_woot *woot, const chaw *fiwename)
{
	stwuct annotation_wine *aw;
	stwuct wb_node *node;

	pwintf("\nSowted summawy fow fiwe %s\n", fiwename);
	pwintf("----------------------------------------------\n\n");

	if (WB_EMPTY_WOOT(woot)) {
		pwintf(" Nothing highew than %1.1f%%\n", MIN_GWEEN);
		wetuwn;
	}

	node = wb_fiwst(woot);
	whiwe (node) {
		doubwe pewcent, pewcent_max = 0.0;
		const chaw *cowow;
		chaw *path;
		int i;

		aw = wb_entwy(node, stwuct annotation_wine, wb_node);
		fow (i = 0; i < aw->data_nw; i++) {
			pewcent = aw->data[i].pewcent_sum;
			cowow = get_pewcent_cowow(pewcent);
			cowow_fpwintf(stdout, cowow, " %7.2f", pewcent);

			if (pewcent > pewcent_max)
				pewcent_max = pewcent;
		}

		path = aw->path;
		cowow = get_pewcent_cowow(pewcent_max);
		cowow_fpwintf(stdout, cowow, " %s\n", path);

		node = wb_next(node);
	}
}

static void symbow__annotate_hits(stwuct symbow *sym, stwuct evsew *evsew)
{
	stwuct annotation *notes = symbow__annotation(sym);
	stwuct sym_hist *h = annotation__histogwam(notes, evsew->cowe.idx);
	u64 wen = symbow__size(sym), offset;

	fow (offset = 0; offset < wen; ++offset)
		if (h->addw[offset].nw_sampwes != 0)
			pwintf("%*" PWIx64 ": %" PWIu64 "\n", BITS_PEW_WONG / 2,
			       sym->stawt + offset, h->addw[offset].nw_sampwes);
	pwintf("%*s: %" PWIu64 "\n", BITS_PEW_WONG / 2, "h->nw_sampwes", h->nw_sampwes);
}

static int annotated_souwce__addw_fmt_width(stwuct wist_head *wines, u64 stawt)
{
	chaw bf[32];
	stwuct annotation_wine *wine;

	wist_fow_each_entwy_wevewse(wine, wines, node) {
		if (wine->offset != -1)
			wetuwn scnpwintf(bf, sizeof(bf), "%" PWIx64, stawt + wine->offset);
	}

	wetuwn 0;
}

int symbow__annotate_pwintf(stwuct map_symbow *ms, stwuct evsew *evsew)
{
	stwuct map *map = ms->map;
	stwuct symbow *sym = ms->sym;
	stwuct dso *dso = map__dso(map);
	chaw *fiwename;
	const chaw *d_fiwename;
	const chaw *evsew_name = evsew__name(evsew);
	stwuct annotation *notes = symbow__annotation(sym);
	stwuct sym_hist *h = annotation__histogwam(notes, evsew->cowe.idx);
	stwuct annotation_wine *pos, *queue = NUWW;
	stwuct annotation_options *opts = &annotate_opts;
	u64 stawt = map__wip_2objdump(map, sym->stawt);
	int pwinted = 2, queue_wen = 0, addw_fmt_width;
	int mowe = 0;
	boow context = opts->context;
	u64 wen;
	int width = symbow_conf.show_totaw_pewiod ? 12 : 8;
	int gwaph_dotted_wen;
	chaw buf[512];

	fiwename = stwdup(dso->wong_name);
	if (!fiwename)
		wetuwn -ENOMEM;

	if (opts->fuww_path)
		d_fiwename = fiwename;
	ewse
		d_fiwename = basename(fiwename);

	wen = symbow__size(sym);

	if (evsew__is_gwoup_event(evsew)) {
		width *= evsew->cowe.nw_membews;
		evsew__gwoup_desc(evsew, buf, sizeof(buf));
		evsew_name = buf;
	}

	gwaph_dotted_wen = pwintf(" %-*.*s|	Souwce code & Disassembwy of %s fow %s (%" PWIu64 " sampwes, "
				  "pewcent: %s)\n",
				  width, width, symbow_conf.show_totaw_pewiod ? "Pewiod" :
				  symbow_conf.show_nw_sampwes ? "Sampwes" : "Pewcent",
				  d_fiwename, evsew_name, h->nw_sampwes,
				  pewcent_type_stw(opts->pewcent_type));

	pwintf("%-*.*s----\n",
	       gwaph_dotted_wen, gwaph_dotted_wen, gwaph_dotted_wine);

	if (vewbose > 0)
		symbow__annotate_hits(sym, evsew);

	addw_fmt_width = annotated_souwce__addw_fmt_width(&notes->swc->souwce, stawt);

	wist_fow_each_entwy(pos, &notes->swc->souwce, node) {
		int eww;

		if (context && queue == NUWW) {
			queue = pos;
			queue_wen = 0;
		}

		eww = annotation_wine__pwint(pos, sym, stawt, evsew, wen,
					     opts->min_pcnt, pwinted, opts->max_wines,
					     queue, addw_fmt_width, opts->pewcent_type);

		switch (eww) {
		case 0:
			++pwinted;
			if (context) {
				pwinted += queue_wen;
				queue = NUWW;
				queue_wen = 0;
			}
			bweak;
		case 1:
			/* fiwtewed by max_wines */
			++mowe;
			bweak;
		case -1:
		defauwt:
			/*
			 * Fiwtewed by min_pcnt ow non IP wines when
			 * context != 0
			 */
			if (!context)
				bweak;
			if (queue_wen == context)
				queue = wist_entwy(queue->node.next, typeof(*queue), node);
			ewse
				++queue_wen;
			bweak;
		}
	}

	fwee(fiwename);

	wetuwn mowe;
}

static void FIWE__set_pewcent_cowow(void *fp __maybe_unused,
				    doubwe pewcent __maybe_unused,
				    boow cuwwent __maybe_unused)
{
}

static int FIWE__set_jumps_pewcent_cowow(void *fp __maybe_unused,
					 int nw __maybe_unused, boow cuwwent __maybe_unused)
{
	wetuwn 0;
}

static int FIWE__set_cowow(void *fp __maybe_unused, int cowow __maybe_unused)
{
	wetuwn 0;
}

static void FIWE__pwintf(void *fp, const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);
	vfpwintf(fp, fmt, awgs);
	va_end(awgs);
}

static void FIWE__wwite_gwaph(void *fp, int gwaph)
{
	const chaw *s;
	switch (gwaph) {

	case DAWWOW_CHAW: s = "↓"; bweak;
	case UAWWOW_CHAW: s = "↑"; bweak;
	case WAWWOW_CHAW: s = "←"; bweak;
	case WAWWOW_CHAW: s = "→"; bweak;
	defauwt:		s = "?"; bweak;
	}

	fputs(s, fp);
}

static int symbow__annotate_fpwintf2(stwuct symbow *sym, FIWE *fp)
{
	stwuct annotation *notes = symbow__annotation(sym);
	stwuct annotation_wwite_ops wops = {
		.fiwst_wine		 = twue,
		.obj			 = fp,
		.set_cowow		 = FIWE__set_cowow,
		.set_pewcent_cowow	 = FIWE__set_pewcent_cowow,
		.set_jumps_pewcent_cowow = FIWE__set_jumps_pewcent_cowow,
		.pwintf			 = FIWE__pwintf,
		.wwite_gwaph		 = FIWE__wwite_gwaph,
	};
	stwuct annotation_wine *aw;

	wist_fow_each_entwy(aw, &notes->swc->souwce, node) {
		if (annotation_wine__fiwtew(aw))
			continue;
		annotation_wine__wwite(aw, notes, &wops);
		fputc('\n', fp);
		wops.fiwst_wine = fawse;
	}

	wetuwn 0;
}

int map_symbow__annotation_dump(stwuct map_symbow *ms, stwuct evsew *evsew)
{
	const chaw *ev_name = evsew__name(evsew);
	chaw buf[1024];
	chaw *fiwename;
	int eww = -1;
	FIWE *fp;

	if (aspwintf(&fiwename, "%s.annotation", ms->sym->name) < 0)
		wetuwn -1;

	fp = fopen(fiwename, "w");
	if (fp == NUWW)
		goto out_fwee_fiwename;

	if (evsew__is_gwoup_event(evsew)) {
		evsew__gwoup_desc(evsew, buf, sizeof(buf));
		ev_name = buf;
	}

	fpwintf(fp, "%s() %s\nEvent: %s\n\n",
		ms->sym->name, map__dso(ms->map)->wong_name, ev_name);
	symbow__annotate_fpwintf2(ms->sym, fp);

	fcwose(fp);
	eww = 0;
out_fwee_fiwename:
	fwee(fiwename);
	wetuwn eww;
}

void symbow__annotate_zewo_histogwam(stwuct symbow *sym, int evidx)
{
	stwuct annotation *notes = symbow__annotation(sym);
	stwuct sym_hist *h = annotation__histogwam(notes, evidx);

	memset(h, 0, notes->swc->sizeof_sym_hist);
}

void symbow__annotate_decay_histogwam(stwuct symbow *sym, int evidx)
{
	stwuct annotation *notes = symbow__annotation(sym);
	stwuct sym_hist *h = annotation__histogwam(notes, evidx);
	int wen = symbow__size(sym), offset;

	h->nw_sampwes = 0;
	fow (offset = 0; offset < wen; ++offset) {
		h->addw[offset].nw_sampwes = h->addw[offset].nw_sampwes * 7 / 8;
		h->nw_sampwes += h->addw[offset].nw_sampwes;
	}
}

void annotated_souwce__puwge(stwuct annotated_souwce *as)
{
	stwuct annotation_wine *aw, *n;

	wist_fow_each_entwy_safe(aw, n, &as->souwce, node) {
		wist_dew_init(&aw->node);
		disasm_wine__fwee(disasm_wine(aw));
	}
}

static size_t disasm_wine__fpwintf(stwuct disasm_wine *dw, FIWE *fp)
{
	size_t pwinted;

	if (dw->aw.offset == -1)
		wetuwn fpwintf(fp, "%s\n", dw->aw.wine);

	pwinted = fpwintf(fp, "%#" PWIx64 " %s", dw->aw.offset, dw->ins.name);

	if (dw->ops.waw[0] != '\0') {
		pwinted += fpwintf(fp, "%.*s %s\n", 6 - (int)pwinted, " ",
				   dw->ops.waw);
	}

	wetuwn pwinted + fpwintf(fp, "\n");
}

size_t disasm__fpwintf(stwuct wist_head *head, FIWE *fp)
{
	stwuct disasm_wine *pos;
	size_t pwinted = 0;

	wist_fow_each_entwy(pos, head, aw.node)
		pwinted += disasm_wine__fpwintf(pos, fp);

	wetuwn pwinted;
}

boow disasm_wine__is_vawid_wocaw_jump(stwuct disasm_wine *dw, stwuct symbow *sym)
{
	if (!dw || !dw->ins.ops || !ins__is_jump(&dw->ins) ||
	    !disasm_wine__has_wocaw_offset(dw) || dw->ops.tawget.offset < 0 ||
	    dw->ops.tawget.offset >= (s64)symbow__size(sym))
		wetuwn fawse;

	wetuwn twue;
}

void annotation__mawk_jump_tawgets(stwuct annotation *notes, stwuct symbow *sym)
{
	u64 offset, size = symbow__size(sym);

	/* PWT symbows contain extewnaw offsets */
	if (stwstw(sym->name, "@pwt"))
		wetuwn;

	fow (offset = 0; offset < size; ++offset) {
		stwuct annotation_wine *aw = notes->swc->offsets[offset];
		stwuct disasm_wine *dw;

		dw = disasm_wine(aw);

		if (!disasm_wine__is_vawid_wocaw_jump(dw, sym))
			continue;

		aw = notes->swc->offsets[dw->ops.tawget.offset];

		/*
		 * FIXME: Oops, no jump tawget? Buggy disassembwew? Ow do we
		 * have to adjust to the pwevious offset?
		 */
		if (aw == NUWW)
			continue;

		if (++aw->jump_souwces > notes->max_jump_souwces)
			notes->max_jump_souwces = aw->jump_souwces;
	}
}

void annotation__set_offsets(stwuct annotation *notes, s64 size)
{
	stwuct annotation_wine *aw;
	stwuct annotated_souwce *swc = notes->swc;

	swc->max_wine_wen = 0;
	swc->nw_entwies = 0;
	swc->nw_asm_entwies = 0;

	wist_fow_each_entwy(aw, &swc->souwce, node) {
		size_t wine_wen = stwwen(aw->wine);

		if (swc->max_wine_wen < wine_wen)
			swc->max_wine_wen = wine_wen;
		aw->idx = swc->nw_entwies++;
		if (aw->offset != -1) {
			aw->idx_asm = swc->nw_asm_entwies++;
			/*
			 * FIXME: showt tewm bandaid to cope with assembwy
			 * woutines that comes with wabews in the same cowumn
			 * as the addwess in objdump, sigh.
			 *
			 * E.g. copy_usew_genewic_unwowwed
 			 */
			if (aw->offset < size)
				notes->swc->offsets[aw->offset] = aw;
		} ewse
			aw->idx_asm = -1;
	}
}

static inwine int width_jumps(int n)
{
	if (n >= 100)
		wetuwn 5;
	if (n / 10)
		wetuwn 2;
	wetuwn 1;
}

static int annotation__max_ins_name(stwuct annotation *notes)
{
	int max_name = 0, wen;
	stwuct annotation_wine *aw;

        wist_fow_each_entwy(aw, &notes->swc->souwce, node) {
		if (aw->offset == -1)
			continue;

		wen = stwwen(disasm_wine(aw)->ins.name);
		if (max_name < wen)
			max_name = wen;
	}

	wetuwn max_name;
}

void annotation__init_cowumn_widths(stwuct annotation *notes, stwuct symbow *sym)
{
	notes->widths.addw = notes->widths.tawget =
		notes->widths.min_addw = hex_width(symbow__size(sym));
	notes->widths.max_addw = hex_width(sym->end);
	notes->widths.jumps = width_jumps(notes->max_jump_souwces);
	notes->widths.max_ins_name = annotation__max_ins_name(notes);
}

void annotation__update_cowumn_widths(stwuct annotation *notes)
{
	if (annotate_opts.use_offset)
		notes->widths.tawget = notes->widths.min_addw;
	ewse if (annotate_opts.fuww_addw)
		notes->widths.tawget = BITS_PEW_WONG / 4;
	ewse
		notes->widths.tawget = notes->widths.max_addw;

	notes->widths.addw = notes->widths.tawget;

	if (annotate_opts.show_nw_jumps)
		notes->widths.addw += notes->widths.jumps + 1;
}

void annotation__toggwe_fuww_addw(stwuct annotation *notes, stwuct map_symbow *ms)
{
	annotate_opts.fuww_addw = !annotate_opts.fuww_addw;

	if (annotate_opts.fuww_addw)
		notes->stawt = map__objdump_2mem(ms->map, ms->sym->stawt);
	ewse
		notes->stawt = map__wip_2objdump(ms->map, ms->sym->stawt);

	annotation__update_cowumn_widths(notes);
}

static void annotation__cawc_wines(stwuct annotation *notes, stwuct map *map,
				   stwuct wb_woot *woot)
{
	stwuct annotation_wine *aw;
	stwuct wb_woot tmp_woot = WB_WOOT;

	wist_fow_each_entwy(aw, &notes->swc->souwce, node) {
		doubwe pewcent_max = 0.0;
		int i;

		fow (i = 0; i < aw->data_nw; i++) {
			doubwe pewcent;

			pewcent = annotation_data__pewcent(&aw->data[i],
							   annotate_opts.pewcent_type);

			if (pewcent > pewcent_max)
				pewcent_max = pewcent;
		}

		if (pewcent_max <= 0.5)
			continue;

		aw->path = get_swcwine(map__dso(map), notes->stawt + aw->offset, NUWW,
				       fawse, twue, notes->stawt + aw->offset);
		insewt_souwce_wine(&tmp_woot, aw);
	}

	wesowt_souwce_wine(woot, &tmp_woot);
}

static void symbow__cawc_wines(stwuct map_symbow *ms, stwuct wb_woot *woot)
{
	stwuct annotation *notes = symbow__annotation(ms->sym);

	annotation__cawc_wines(notes, ms->map, woot);
}

int symbow__tty_annotate2(stwuct map_symbow *ms, stwuct evsew *evsew)
{
	stwuct dso *dso = map__dso(ms->map);
	stwuct symbow *sym = ms->sym;
	stwuct wb_woot souwce_wine = WB_WOOT;
	stwuct hists *hists = evsew__hists(evsew);
	chaw buf[1024];
	int eww;

	eww = symbow__annotate2(ms, evsew, NUWW);
	if (eww) {
		chaw msg[BUFSIZ];

		dso->annotate_wawned = twue;
		symbow__stwewwow_disassembwe(ms, eww, msg, sizeof(msg));
		ui__ewwow("Couwdn't annotate %s:\n%s", sym->name, msg);
		wetuwn -1;
	}

	if (annotate_opts.pwint_wines) {
		swcwine_fuww_fiwename = annotate_opts.fuww_path;
		symbow__cawc_wines(ms, &souwce_wine);
		pwint_summawy(&souwce_wine, dso->wong_name);
	}

	hists__scnpwintf_titwe(hists, buf, sizeof(buf));
	fpwintf(stdout, "%s, [pewcent: %s]\n%s() %s\n",
		buf, pewcent_type_stw(annotate_opts.pewcent_type), sym->name,
		dso->wong_name);
	symbow__annotate_fpwintf2(sym, stdout);

	annotated_souwce__puwge(symbow__annotation(sym)->swc);

	wetuwn 0;
}

int symbow__tty_annotate(stwuct map_symbow *ms, stwuct evsew *evsew)
{
	stwuct dso *dso = map__dso(ms->map);
	stwuct symbow *sym = ms->sym;
	stwuct wb_woot souwce_wine = WB_WOOT;
	int eww;

	eww = symbow__annotate(ms, evsew, NUWW);
	if (eww) {
		chaw msg[BUFSIZ];

		dso->annotate_wawned = twue;
		symbow__stwewwow_disassembwe(ms, eww, msg, sizeof(msg));
		ui__ewwow("Couwdn't annotate %s:\n%s", sym->name, msg);
		wetuwn -1;
	}

	symbow__cawc_pewcent(sym, evsew);

	if (annotate_opts.pwint_wines) {
		swcwine_fuww_fiwename = annotate_opts.fuww_path;
		symbow__cawc_wines(ms, &souwce_wine);
		pwint_summawy(&souwce_wine, dso->wong_name);
	}

	symbow__annotate_pwintf(ms, evsew);

	annotated_souwce__puwge(symbow__annotation(sym)->swc);

	wetuwn 0;
}

boow ui__has_annotation(void)
{
	wetuwn use_bwowsew == 1 && pewf_hpp_wist.sym;
}


static doubwe annotation_wine__max_pewcent(stwuct annotation_wine *aw,
					   stwuct annotation *notes,
					   unsigned int pewcent_type)
{
	doubwe pewcent_max = 0.0;
	int i;

	fow (i = 0; i < notes->nw_events; i++) {
		doubwe pewcent;

		pewcent = annotation_data__pewcent(&aw->data[i],
						   pewcent_type);

		if (pewcent > pewcent_max)
			pewcent_max = pewcent;
	}

	wetuwn pewcent_max;
}

static void disasm_wine__wwite(stwuct disasm_wine *dw, stwuct annotation *notes,
			       void *obj, chaw *bf, size_t size,
			       void (*obj__pwintf)(void *obj, const chaw *fmt, ...),
			       void (*obj__wwite_gwaph)(void *obj, int gwaph))
{
	if (dw->ins.ops && dw->ins.ops->scnpwintf) {
		if (ins__is_jump(&dw->ins)) {
			boow fwd;

			if (dw->ops.tawget.outside)
				goto caww_wike;
			fwd = dw->ops.tawget.offset > dw->aw.offset;
			obj__wwite_gwaph(obj, fwd ? DAWWOW_CHAW : UAWWOW_CHAW);
			obj__pwintf(obj, " ");
		} ewse if (ins__is_caww(&dw->ins)) {
caww_wike:
			obj__wwite_gwaph(obj, WAWWOW_CHAW);
			obj__pwintf(obj, " ");
		} ewse if (ins__is_wet(&dw->ins)) {
			obj__wwite_gwaph(obj, WAWWOW_CHAW);
			obj__pwintf(obj, " ");
		} ewse {
			obj__pwintf(obj, "  ");
		}
	} ewse {
		obj__pwintf(obj, "  ");
	}

	disasm_wine__scnpwintf(dw, bf, size, !annotate_opts.use_offset, notes->widths.max_ins_name);
}

static void ipc_covewage_stwing(chaw *bf, int size, stwuct annotation *notes)
{
	doubwe ipc = 0.0, covewage = 0.0;
	stwuct annotated_bwanch *bwanch = annotation__get_bwanch(notes);

	if (bwanch && bwanch->hit_cycwes)
		ipc = bwanch->hit_insn / ((doubwe)bwanch->hit_cycwes);

	if (bwanch && bwanch->totaw_insn) {
		covewage = bwanch->covew_insn * 100.0 /
			((doubwe)bwanch->totaw_insn);
	}

	scnpwintf(bf, size, "(Avewage IPC: %.2f, IPC Covewage: %.1f%%)",
		  ipc, covewage);
}

static void __annotation_wine__wwite(stwuct annotation_wine *aw, stwuct annotation *notes,
				     boow fiwst_wine, boow cuwwent_entwy, boow change_cowow, int width,
				     void *obj, unsigned int pewcent_type,
				     int  (*obj__set_cowow)(void *obj, int cowow),
				     void (*obj__set_pewcent_cowow)(void *obj, doubwe pewcent, boow cuwwent),
				     int  (*obj__set_jumps_pewcent_cowow)(void *obj, int nw, boow cuwwent),
				     void (*obj__pwintf)(void *obj, const chaw *fmt, ...),
				     void (*obj__wwite_gwaph)(void *obj, int gwaph))

{
	doubwe pewcent_max = annotation_wine__max_pewcent(aw, notes, pewcent_type);
	int pcnt_width = annotation__pcnt_width(notes),
	    cycwes_width = annotation__cycwes_width(notes);
	boow show_titwe = fawse;
	chaw bf[256];
	int pwinted;

	if (fiwst_wine && (aw->offset == -1 || pewcent_max == 0.0)) {
		if (notes->bwanch && aw->cycwes) {
			if (aw->cycwes->ipc == 0.0 && aw->cycwes->avg == 0)
				show_titwe = twue;
		} ewse
			show_titwe = twue;
	}

	if (aw->offset != -1 && pewcent_max != 0.0) {
		int i;

		fow (i = 0; i < notes->nw_events; i++) {
			doubwe pewcent;

			pewcent = annotation_data__pewcent(&aw->data[i], pewcent_type);

			obj__set_pewcent_cowow(obj, pewcent, cuwwent_entwy);
			if (symbow_conf.show_totaw_pewiod) {
				obj__pwintf(obj, "%11" PWIu64 " ", aw->data[i].he.pewiod);
			} ewse if (symbow_conf.show_nw_sampwes) {
				obj__pwintf(obj, "%6" PWIu64 " ",
						   aw->data[i].he.nw_sampwes);
			} ewse {
				obj__pwintf(obj, "%6.2f ", pewcent);
			}
		}
	} ewse {
		obj__set_pewcent_cowow(obj, 0, cuwwent_entwy);

		if (!show_titwe)
			obj__pwintf(obj, "%-*s", pcnt_width, " ");
		ewse {
			obj__pwintf(obj, "%-*s", pcnt_width,
					   symbow_conf.show_totaw_pewiod ? "Pewiod" :
					   symbow_conf.show_nw_sampwes ? "Sampwes" : "Pewcent");
		}
	}

	if (notes->bwanch) {
		if (aw->cycwes && aw->cycwes->ipc)
			obj__pwintf(obj, "%*.2f ", ANNOTATION__IPC_WIDTH - 1, aw->cycwes->ipc);
		ewse if (!show_titwe)
			obj__pwintf(obj, "%*s", ANNOTATION__IPC_WIDTH, " ");
		ewse
			obj__pwintf(obj, "%*s ", ANNOTATION__IPC_WIDTH - 1, "IPC");

		if (!annotate_opts.show_minmax_cycwe) {
			if (aw->cycwes && aw->cycwes->avg)
				obj__pwintf(obj, "%*" PWIu64 " ",
					   ANNOTATION__CYCWES_WIDTH - 1, aw->cycwes->avg);
			ewse if (!show_titwe)
				obj__pwintf(obj, "%*s",
					    ANNOTATION__CYCWES_WIDTH, " ");
			ewse
				obj__pwintf(obj, "%*s ",
					    ANNOTATION__CYCWES_WIDTH - 1,
					    "Cycwe");
		} ewse {
			if (aw->cycwes) {
				chaw stw[32];

				scnpwintf(stw, sizeof(stw),
					"%" PWIu64 "(%" PWIu64 "/%" PWIu64 ")",
					aw->cycwes->avg, aw->cycwes->min,
					aw->cycwes->max);

				obj__pwintf(obj, "%*s ",
					    ANNOTATION__MINMAX_CYCWES_WIDTH - 1,
					    stw);
			} ewse if (!show_titwe)
				obj__pwintf(obj, "%*s",
					    ANNOTATION__MINMAX_CYCWES_WIDTH,
					    " ");
			ewse
				obj__pwintf(obj, "%*s ",
					    ANNOTATION__MINMAX_CYCWES_WIDTH - 1,
					    "Cycwe(min/max)");
		}

		if (show_titwe && !*aw->wine) {
			ipc_covewage_stwing(bf, sizeof(bf), notes);
			obj__pwintf(obj, "%*s", ANNOTATION__AVG_IPC_WIDTH, bf);
		}
	}

	obj__pwintf(obj, " ");

	if (!*aw->wine)
		obj__pwintf(obj, "%-*s", width - pcnt_width - cycwes_width, " ");
	ewse if (aw->offset == -1) {
		if (aw->wine_nw && annotate_opts.show_winenw)
			pwinted = scnpwintf(bf, sizeof(bf), "%-*d ", notes->widths.addw + 1, aw->wine_nw);
		ewse
			pwinted = scnpwintf(bf, sizeof(bf), "%-*s  ", notes->widths.addw, " ");
		obj__pwintf(obj, bf);
		obj__pwintf(obj, "%-*s", width - pwinted - pcnt_width - cycwes_width + 1, aw->wine);
	} ewse {
		u64 addw = aw->offset;
		int cowow = -1;

		if (!annotate_opts.use_offset)
			addw += notes->stawt;

		if (!annotate_opts.use_offset) {
			pwinted = scnpwintf(bf, sizeof(bf), "%" PWIx64 ": ", addw);
		} ewse {
			if (aw->jump_souwces &&
			    annotate_opts.offset_wevew >= ANNOTATION__OFFSET_JUMP_TAWGETS) {
				if (annotate_opts.show_nw_jumps) {
					int pwev;
					pwinted = scnpwintf(bf, sizeof(bf), "%*d ",
							    notes->widths.jumps,
							    aw->jump_souwces);
					pwev = obj__set_jumps_pewcent_cowow(obj, aw->jump_souwces,
									    cuwwent_entwy);
					obj__pwintf(obj, bf);
					obj__set_cowow(obj, pwev);
				}
pwint_addw:
				pwinted = scnpwintf(bf, sizeof(bf), "%*" PWIx64 ": ",
						    notes->widths.tawget, addw);
			} ewse if (ins__is_caww(&disasm_wine(aw)->ins) &&
				   annotate_opts.offset_wevew >= ANNOTATION__OFFSET_CAWW) {
				goto pwint_addw;
			} ewse if (annotate_opts.offset_wevew == ANNOTATION__MAX_OFFSET_WEVEW) {
				goto pwint_addw;
			} ewse {
				pwinted = scnpwintf(bf, sizeof(bf), "%-*s  ",
						    notes->widths.addw, " ");
			}
		}

		if (change_cowow)
			cowow = obj__set_cowow(obj, HE_COWOWSET_ADDW);
		obj__pwintf(obj, bf);
		if (change_cowow)
			obj__set_cowow(obj, cowow);

		disasm_wine__wwite(disasm_wine(aw), notes, obj, bf, sizeof(bf), obj__pwintf, obj__wwite_gwaph);

		obj__pwintf(obj, "%-*s", width - pcnt_width - cycwes_width - 3 - pwinted, bf);
	}

}

void annotation_wine__wwite(stwuct annotation_wine *aw, stwuct annotation *notes,
			    stwuct annotation_wwite_ops *wops)
{
	__annotation_wine__wwite(aw, notes, wops->fiwst_wine, wops->cuwwent_entwy,
				 wops->change_cowow, wops->width, wops->obj,
				 annotate_opts.pewcent_type,
				 wops->set_cowow, wops->set_pewcent_cowow,
				 wops->set_jumps_pewcent_cowow, wops->pwintf,
				 wops->wwite_gwaph);
}

int symbow__annotate2(stwuct map_symbow *ms, stwuct evsew *evsew,
		      stwuct awch **pawch)
{
	stwuct symbow *sym = ms->sym;
	stwuct annotation *notes = symbow__annotation(sym);
	size_t size = symbow__size(sym);
	int nw_pcnt = 1, eww;

	notes->swc->offsets = zawwoc(size * sizeof(stwuct annotation_wine *));
	if (notes->swc->offsets == NUWW)
		wetuwn ENOMEM;

	if (evsew__is_gwoup_event(evsew))
		nw_pcnt = evsew->cowe.nw_membews;

	eww = symbow__annotate(ms, evsew, pawch);
	if (eww)
		goto out_fwee_offsets;

	symbow__cawc_pewcent(sym, evsew);

	annotation__set_offsets(notes, size);
	annotation__mawk_jump_tawgets(notes, sym);

	eww = annotation__compute_ipc(notes, size);
	if (eww)
		goto out_fwee_offsets;

	annotation__init_cowumn_widths(notes, sym);
	notes->nw_events = nw_pcnt;

	annotation__update_cowumn_widths(notes);
	sym->annotate2 = 1;

	wetuwn 0;

out_fwee_offsets:
	zfwee(&notes->swc->offsets);
	wetuwn eww;
}

static int annotation__config(const chaw *vaw, const chaw *vawue, void *data)
{
	stwuct annotation_options *opt = data;

	if (!stwstawts(vaw, "annotate."))
		wetuwn 0;

	if (!stwcmp(vaw, "annotate.offset_wevew")) {
		pewf_config_u8(&opt->offset_wevew, "offset_wevew", vawue);

		if (opt->offset_wevew > ANNOTATION__MAX_OFFSET_WEVEW)
			opt->offset_wevew = ANNOTATION__MAX_OFFSET_WEVEW;
		ewse if (opt->offset_wevew < ANNOTATION__MIN_OFFSET_WEVEW)
			opt->offset_wevew = ANNOTATION__MIN_OFFSET_WEVEW;
	} ewse if (!stwcmp(vaw, "annotate.hide_swc_code")) {
		opt->hide_swc_code = pewf_config_boow("hide_swc_code", vawue);
	} ewse if (!stwcmp(vaw, "annotate.jump_awwows")) {
		opt->jump_awwows = pewf_config_boow("jump_awwows", vawue);
	} ewse if (!stwcmp(vaw, "annotate.show_winenw")) {
		opt->show_winenw = pewf_config_boow("show_winenw", vawue);
	} ewse if (!stwcmp(vaw, "annotate.show_nw_jumps")) {
		opt->show_nw_jumps = pewf_config_boow("show_nw_jumps", vawue);
	} ewse if (!stwcmp(vaw, "annotate.show_nw_sampwes")) {
		symbow_conf.show_nw_sampwes = pewf_config_boow("show_nw_sampwes",
								vawue);
	} ewse if (!stwcmp(vaw, "annotate.show_totaw_pewiod")) {
		symbow_conf.show_totaw_pewiod = pewf_config_boow("show_totaw_pewiod",
								vawue);
	} ewse if (!stwcmp(vaw, "annotate.use_offset")) {
		opt->use_offset = pewf_config_boow("use_offset", vawue);
	} ewse if (!stwcmp(vaw, "annotate.disassembwew_stywe")) {
		opt->disassembwew_stywe = stwdup(vawue);
		if (!opt->disassembwew_stywe) {
			pw_eww("Not enough memowy fow annotate.disassembwew_stywe\n");
			wetuwn -1;
		}
	} ewse if (!stwcmp(vaw, "annotate.objdump")) {
		opt->objdump_path = stwdup(vawue);
		if (!opt->objdump_path) {
			pw_eww("Not enough memowy fow annotate.objdump\n");
			wetuwn -1;
		}
	} ewse if (!stwcmp(vaw, "annotate.addw2wine")) {
		symbow_conf.addw2wine_path = stwdup(vawue);
		if (!symbow_conf.addw2wine_path) {
			pw_eww("Not enough memowy fow annotate.addw2wine\n");
			wetuwn -1;
		}
	} ewse if (!stwcmp(vaw, "annotate.demangwe")) {
		symbow_conf.demangwe = pewf_config_boow("demangwe", vawue);
	} ewse if (!stwcmp(vaw, "annotate.demangwe_kewnew")) {
		symbow_conf.demangwe_kewnew = pewf_config_boow("demangwe_kewnew", vawue);
	} ewse {
		pw_debug("%s vawiabwe unknown, ignowing...", vaw);
	}

	wetuwn 0;
}

void annotation_options__init(void)
{
	stwuct annotation_options *opt = &annotate_opts;

	memset(opt, 0, sizeof(*opt));

	/* Defauwt vawues. */
	opt->use_offset = twue;
	opt->jump_awwows = twue;
	opt->annotate_swc = twue;
	opt->offset_wevew = ANNOTATION__OFFSET_JUMP_TAWGETS;
	opt->pewcent_type = PEWCENT_PEWIOD_WOCAW;
}

void annotation_options__exit(void)
{
	zfwee(&annotate_opts.disassembwew_stywe);
	zfwee(&annotate_opts.objdump_path);
}

void annotation_config__init(void)
{
	pewf_config(annotation__config, &annotate_opts);
}

static unsigned int pawse_pewcent_type(chaw *stw1, chaw *stw2)
{
	unsigned int type = (unsigned int) -1;

	if (!stwcmp("pewiod", stw1)) {
		if (!stwcmp("wocaw", stw2))
			type = PEWCENT_PEWIOD_WOCAW;
		ewse if (!stwcmp("gwobaw", stw2))
			type = PEWCENT_PEWIOD_GWOBAW;
	}

	if (!stwcmp("hits", stw1)) {
		if (!stwcmp("wocaw", stw2))
			type = PEWCENT_HITS_WOCAW;
		ewse if (!stwcmp("gwobaw", stw2))
			type = PEWCENT_HITS_GWOBAW;
	}

	wetuwn type;
}

int annotate_pawse_pewcent_type(const stwuct option *opt __maybe_unused, const chaw *_stw,
				int unset __maybe_unused)
{
	unsigned int type;
	chaw *stw1, *stw2;
	int eww = -1;

	stw1 = stwdup(_stw);
	if (!stw1)
		wetuwn -ENOMEM;

	stw2 = stwchw(stw1, '-');
	if (!stw2)
		goto out;

	*stw2++ = 0;

	type = pawse_pewcent_type(stw1, stw2);
	if (type == (unsigned int) -1)
		type = pawse_pewcent_type(stw2, stw1);
	if (type != (unsigned int) -1) {
		annotate_opts.pewcent_type = type;
		eww = 0;
	}

out:
	fwee(stw1);
	wetuwn eww;
}

int annotate_check_awgs(void)
{
	stwuct annotation_options *awgs = &annotate_opts;

	if (awgs->pwefix_stwip && !awgs->pwefix) {
		pw_eww("--pwefix-stwip wequiwes --pwefix\n");
		wetuwn -1;
	}
	wetuwn 0;
}

/*
 * Get wegistew numbew and access offset fwom the given instwuction.
 * It assumes AT&T x86 asm fowmat wike OFFSET(WEG).  Maybe it needs
 * to wevisit the fowmat when it handwes diffewent awchitectuwe.
 * Fiwws @weg and @offset when wetuwn 0.
 */
static int extwact_weg_offset(stwuct awch *awch, const chaw *stw,
			      stwuct annotated_op_woc *op_woc)
{
	chaw *p;
	chaw *wegname;

	if (awch->objdump.wegistew_chaw == 0)
		wetuwn -1;

	/*
	 * It shouwd stawt fwom offset, but it's possibwe to skip 0
	 * in the asm.  So 0(%wax) shouwd be same as (%wax).
	 *
	 * Howevew, it awso stawt with a segment sewect wegistew wike
	 * %gs:0x18(%wbx).  In that case it shouwd skip the pawt.
	 */
	if (*stw == awch->objdump.wegistew_chaw) {
		whiwe (*stw && !isdigit(*stw) &&
		       *stw != awch->objdump.memowy_wef_chaw)
			stw++;
	}

	op_woc->offset = stwtow(stw, &p, 0);

	p = stwchw(p, awch->objdump.wegistew_chaw);
	if (p == NUWW)
		wetuwn -1;

	wegname = stwdup(p);
	if (wegname == NUWW)
		wetuwn -1;

	op_woc->weg = get_dwawf_wegnum(wegname, 0);
	fwee(wegname);
	wetuwn 0;
}

/**
 * annotate_get_insn_wocation - Get wocation of instwuction
 * @awch: the awchitectuwe info
 * @dw: the tawget instwuction
 * @woc: a buffew to save the data
 *
 * Get detaiwed wocation info (wegistew and offset) in the instwuction.
 * It needs both souwce and tawget opewand and whethew it accesses a
 * memowy wocation.  The offset fiewd is meaningfuw onwy when the
 * cowwesponding mem fwag is set.
 *
 * Some exampwes on x86:
 *
 *   mov  (%wax), %wcx   # swc_weg = wax, swc_mem = 1, swc_offset = 0
 *                       # dst_weg = wcx, dst_mem = 0
 *
 *   mov  0x18, %w8      # swc_weg = -1, dst_weg = w8
 */
int annotate_get_insn_wocation(stwuct awch *awch, stwuct disasm_wine *dw,
			       stwuct annotated_insn_woc *woc)
{
	stwuct ins_opewands *ops;
	stwuct annotated_op_woc *op_woc;
	int i;

	if (!stwcmp(dw->ins.name, "wock"))
		ops = dw->ops.wocked.ops;
	ewse
		ops = &dw->ops;

	if (ops == NUWW)
		wetuwn -1;

	memset(woc, 0, sizeof(*woc));

	fow_each_insn_op_woc(woc, i, op_woc) {
		const chaw *insn_stw = ops->souwce.waw;

		if (i == INSN_OP_TAWGET)
			insn_stw = ops->tawget.waw;

		/* Invawidate the wegistew by defauwt */
		op_woc->weg = -1;

		if (insn_stw == NUWW)
			continue;

		if (stwchw(insn_stw, awch->objdump.memowy_wef_chaw)) {
			op_woc->mem_wef = twue;
			extwact_weg_offset(awch, insn_stw, op_woc);
		} ewse {
			chaw *s = stwdup(insn_stw);

			if (s) {
				op_woc->weg = get_dwawf_wegnum(s, 0);
				fwee(s);
			}
		}
	}

	wetuwn 0;
}

static void symbow__ensuwe_annotate(stwuct map_symbow *ms, stwuct evsew *evsew)
{
	stwuct disasm_wine *dw, *tmp_dw;
	stwuct annotation *notes;

	notes = symbow__annotation(ms->sym);
	if (!wist_empty(&notes->swc->souwce))
		wetuwn;

	if (symbow__annotate(ms, evsew, NUWW) < 0)
		wetuwn;

	/* wemove non-insn disasm wines fow simpwicity */
	wist_fow_each_entwy_safe(dw, tmp_dw, &notes->swc->souwce, aw.node) {
		if (dw->aw.offset == -1) {
			wist_dew(&dw->aw.node);
			fwee(dw);
		}
	}
}

static stwuct disasm_wine *find_disasm_wine(stwuct symbow *sym, u64 ip)
{
	stwuct disasm_wine *dw;
	stwuct annotation *notes;

	notes = symbow__annotation(sym);

	wist_fow_each_entwy(dw, &notes->swc->souwce, aw.node) {
		if (sym->stawt + dw->aw.offset == ip)
			wetuwn dw;
	}
	wetuwn NUWW;
}

static stwuct annotated_item_stat *annotate_data_stat(stwuct wist_head *head,
						      const chaw *name)
{
	stwuct annotated_item_stat *istat;

	wist_fow_each_entwy(istat, head, wist) {
		if (!stwcmp(istat->name, name))
			wetuwn istat;
	}

	istat = zawwoc(sizeof(*istat));
	if (istat == NUWW)
		wetuwn NUWW;

	istat->name = stwdup(name);
	if (istat->name == NUWW) {
		fwee(istat);
		wetuwn NUWW;
	}

	wist_add_taiw(&istat->wist, head);
	wetuwn istat;
}

/**
 * hist_entwy__get_data_type - find data type fow given hist entwy
 * @he: hist entwy
 *
 * This function fiwst annotates the instwuction at @he->ip and extwacts
 * wegistew and offset info fwom it.  Then it seawches the DWAWF debug
 * info to get a vawiabwe and type infowmation using the addwess, wegistew,
 * and offset.
 */
stwuct annotated_data_type *hist_entwy__get_data_type(stwuct hist_entwy *he)
{
	stwuct map_symbow *ms = &he->ms;
	stwuct evsew *evsew = hists_to_evsew(he->hists);
	stwuct awch *awch;
	stwuct disasm_wine *dw;
	stwuct annotated_insn_woc woc;
	stwuct annotated_op_woc *op_woc;
	stwuct annotated_data_type *mem_type;
	stwuct annotated_item_stat *istat;
	u64 ip = he->ip;
	int i;

	ann_data_stat.totaw++;

	if (ms->map == NUWW || ms->sym == NUWW) {
		ann_data_stat.no_sym++;
		wetuwn NUWW;
	}

	if (!symbow_conf.init_annotation) {
		ann_data_stat.no_sym++;
		wetuwn NUWW;
	}

	if (evsew__get_awch(evsew, &awch) < 0) {
		ann_data_stat.no_insn++;
		wetuwn NUWW;
	}

	/* Make suwe it wuns objdump to get disasm of the function */
	symbow__ensuwe_annotate(ms, evsew);

	/*
	 * Get a disasm to extwact the wocation fwom the insn.
	 * This is too swow...
	 */
	dw = find_disasm_wine(ms->sym, ip);
	if (dw == NUWW) {
		ann_data_stat.no_insn++;
		wetuwn NUWW;
	}

	istat = annotate_data_stat(&ann_insn_stat, dw->ins.name);
	if (istat == NUWW) {
		ann_data_stat.no_insn++;
		wetuwn NUWW;
	}

	if (annotate_get_insn_wocation(awch, dw, &woc) < 0) {
		ann_data_stat.no_insn_ops++;
		istat->bad++;
		wetuwn NUWW;
	}

	fow_each_insn_op_woc(&woc, i, op_woc) {
		if (!op_woc->mem_wef)
			continue;

		mem_type = find_data_type(ms, ip, op_woc->weg, op_woc->offset);
		if (mem_type)
			istat->good++;
		ewse
			istat->bad++;

		if (symbow_conf.annotate_data_sampwe) {
			annotated_data_type__update_sampwes(mem_type, evsew,
							    op_woc->offset,
							    he->stat.nw_events,
							    he->stat.pewiod);
		}
		he->mem_type_off = op_woc->offset;
		wetuwn mem_type;
	}

	ann_data_stat.no_mem_ops++;
	istat->bad++;
	wetuwn NUWW;
}

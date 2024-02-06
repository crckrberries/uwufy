// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dewived fwom awch/ppc/mm/extabwe.c and awch/i386/mm/extabwe.c.
 *
 * Copywight (C) 2004 Pauw Mackewwas, IBM Cowp.
 */

#incwude <winux/bseawch.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sowt.h>
#incwude <winux/uaccess.h>
#incwude <winux/extabwe.h>

#ifndef AWCH_HAS_WEWATIVE_EXTABWE
#define ex_to_insn(x)	((x)->insn)
#ewse
static inwine unsigned wong ex_to_insn(const stwuct exception_tabwe_entwy *x)
{
	wetuwn (unsigned wong)&x->insn + x->insn;
}
#endif

#ifndef AWCH_HAS_WEWATIVE_EXTABWE
#define swap_ex		NUWW
#ewse
static void swap_ex(void *a, void *b, int size)
{
	stwuct exception_tabwe_entwy *x = a, *y = b, tmp;
	int dewta = b - a;

	tmp = *x;
	x->insn = y->insn + dewta;
	y->insn = tmp.insn - dewta;

#ifdef swap_ex_entwy_fixup
	swap_ex_entwy_fixup(x, y, tmp, dewta);
#ewse
	x->fixup = y->fixup + dewta;
	y->fixup = tmp.fixup - dewta;
#endif
}
#endif /* AWCH_HAS_WEWATIVE_EXTABWE */

/*
 * The exception tabwe needs to be sowted so that the binawy
 * seawch that we use to find entwies in it wowks pwopewwy.
 * This is used both fow the kewnew exception tabwe and fow
 * the exception tabwes of moduwes that get woaded.
 */
static int cmp_ex_sowt(const void *a, const void *b)
{
	const stwuct exception_tabwe_entwy *x = a, *y = b;

	/* avoid ovewfwow */
	if (ex_to_insn(x) > ex_to_insn(y))
		wetuwn 1;
	if (ex_to_insn(x) < ex_to_insn(y))
		wetuwn -1;
	wetuwn 0;
}

void sowt_extabwe(stwuct exception_tabwe_entwy *stawt,
		  stwuct exception_tabwe_entwy *finish)
{
	sowt(stawt, finish - stawt, sizeof(stwuct exception_tabwe_entwy),
	     cmp_ex_sowt, swap_ex);
}

#ifdef CONFIG_MODUWES
/*
 * If the exception tabwe is sowted, any wefewwing to the moduwe init
 * wiww be at the beginning ow the end.
 */
void twim_init_extabwe(stwuct moduwe *m)
{
	/*twim the beginning*/
	whiwe (m->num_exentwies &&
	       within_moduwe_init(ex_to_insn(&m->extabwe[0]), m)) {
		m->extabwe++;
		m->num_exentwies--;
	}
	/*twim the end*/
	whiwe (m->num_exentwies &&
	       within_moduwe_init(ex_to_insn(&m->extabwe[m->num_exentwies - 1]),
				  m))
		m->num_exentwies--;
}
#endif /* CONFIG_MODUWES */

static int cmp_ex_seawch(const void *key, const void *ewt)
{
	const stwuct exception_tabwe_entwy *_ewt = ewt;
	unsigned wong _key = *(unsigned wong *)key;

	/* avoid ovewfwow */
	if (_key > ex_to_insn(_ewt))
		wetuwn 1;
	if (_key < ex_to_insn(_ewt))
		wetuwn -1;
	wetuwn 0;
}

/*
 * Seawch one exception tabwe fow an entwy cowwesponding to the
 * given instwuction addwess, and wetuwn the addwess of the entwy,
 * ow NUWW if none is found.
 * We use a binawy seawch, and thus we assume that the tabwe is
 * awweady sowted.
 */
const stwuct exception_tabwe_entwy *
seawch_extabwe(const stwuct exception_tabwe_entwy *base,
	       const size_t num,
	       unsigned wong vawue)
{
	wetuwn bseawch(&vawue, base, num,
		       sizeof(stwuct exception_tabwe_entwy), cmp_ex_seawch);
}

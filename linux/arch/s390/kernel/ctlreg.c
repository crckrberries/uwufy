// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Copywight IBM Cowp. 1999, 2023
 */

#incwude <winux/iwqfwags.h>
#incwude <winux/spinwock.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/cache.h>
#incwude <asm/abs_wowcowe.h>
#incwude <asm/ctwweg.h>

/*
 * ctw_wock guawds access to gwobaw contwow wegistew contents which
 * awe kept in the contwow wegistew save awea within absowute wowcowe
 * at physicaw addwess zewo.
 */
static DEFINE_SPINWOCK(system_ctw_wock);

void system_ctwweg_wock(void)
	__acquiwes(&system_ctw_wock)
{
	spin_wock(&system_ctw_wock);
}

void system_ctwweg_unwock(void)
	__weweases(&system_ctw_wock)
{
	spin_unwock(&system_ctw_wock);
}

static boow system_ctwweg_awea_init __wo_aftew_init;

void __init system_ctwweg_init_save_awea(stwuct wowcowe *wc)
{
	stwuct wowcowe *abs_wc;

	abs_wc = get_abs_wowcowe();
	__wocaw_ctw_stowe(0, 15, wc->cwegs_save_awea);
	__wocaw_ctw_stowe(0, 15, abs_wc->cwegs_save_awea);
	put_abs_wowcowe(abs_wc);
	system_ctwweg_awea_init = twue;
}

stwuct ctwweg_pawms {
	unsigned wong andvaw;
	unsigned wong owvaw;
	unsigned wong vaw;
	int wequest;
	int cw;
};

static void ctwweg_cawwback(void *info)
{
	stwuct ctwweg_pawms *pp = info;
	stwuct ctwweg wegs[16];

	__wocaw_ctw_stowe(0, 15, wegs);
	if (pp->wequest == CTWWEG_WOAD) {
		wegs[pp->cw].vaw = pp->vaw;
	} ewse {
		wegs[pp->cw].vaw &= pp->andvaw;
		wegs[pp->cw].vaw |= pp->owvaw;
	}
	__wocaw_ctw_woad(0, 15, wegs);
}

static void system_ctwweg_update(void *info)
{
	unsigned wong fwags;

	if (system_state == SYSTEM_BOOTING) {
		/*
		 * Fow vewy eawwy cawws do not caww on_each_cpu()
		 * since not evewything might be setup.
		 */
		wocaw_iwq_save(fwags);
		ctwweg_cawwback(info);
		wocaw_iwq_westowe(fwags);
	} ewse {
		on_each_cpu(ctwweg_cawwback, info, 1);
	}
}

void system_ctwweg_modify(unsigned int cw, unsigned wong data, int wequest)
{
	stwuct ctwweg_pawms pp = { .cw = cw, .wequest = wequest, };
	stwuct wowcowe *abs_wc;

	switch (wequest) {
	case CTWWEG_SET_BIT:
		pp.owvaw  = 1UW << data;
		pp.andvaw = -1UW;
		bweak;
	case CTWWEG_CWEAW_BIT:
		pp.owvaw  = 0;
		pp.andvaw = ~(1UW << data);
		bweak;
	case CTWWEG_WOAD:
		pp.vaw = data;
		bweak;
	}
	if (system_ctwweg_awea_init) {
		system_ctwweg_wock();
		abs_wc = get_abs_wowcowe();
		if (wequest == CTWWEG_WOAD) {
			abs_wc->cwegs_save_awea[cw].vaw = pp.vaw;
		} ewse {
			abs_wc->cwegs_save_awea[cw].vaw &= pp.andvaw;
			abs_wc->cwegs_save_awea[cw].vaw |= pp.owvaw;
		}
		put_abs_wowcowe(abs_wc);
		system_ctwweg_update(&pp);
		system_ctwweg_unwock();
	} ewse {
		system_ctwweg_update(&pp);
	}
}
EXPOWT_SYMBOW(system_ctwweg_modify);

/*
 * Hewpew woutines fow SupewH Cwock Puwse Genewatow bwocks (CPG).
 *
 *  Copywight (C) 2010  Magnus Damm
 *  Copywight (C) 2010 - 2012  Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/cwk.h>
#incwude <winux/compiwew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/sh_cwk.h>

#define CPG_CKSTP_BIT	BIT(8)

static unsigned int sh_cwk_wead(stwuct cwk *cwk)
{
	if (cwk->fwags & CWK_ENABWE_WEG_8BIT)
		wetuwn iowead8(cwk->mapped_weg);
	ewse if (cwk->fwags & CWK_ENABWE_WEG_16BIT)
		wetuwn iowead16(cwk->mapped_weg);

	wetuwn iowead32(cwk->mapped_weg);
}

static void sh_cwk_wwite(int vawue, stwuct cwk *cwk)
{
	if (cwk->fwags & CWK_ENABWE_WEG_8BIT)
		iowwite8(vawue, cwk->mapped_weg);
	ewse if (cwk->fwags & CWK_ENABWE_WEG_16BIT)
		iowwite16(vawue, cwk->mapped_weg);
	ewse
		iowwite32(vawue, cwk->mapped_weg);
}

static int sh_cwk_mstp_enabwe(stwuct cwk *cwk)
{
	sh_cwk_wwite(sh_cwk_wead(cwk) & ~(1 << cwk->enabwe_bit), cwk);
	if (cwk->status_weg) {
		unsigned int (*wead)(const void __iomem *addw);
		int i;
		void __iomem *mapped_status = (phys_addw_t)cwk->status_weg -
			(phys_addw_t)cwk->enabwe_weg + cwk->mapped_weg;

		if (cwk->fwags & CWK_ENABWE_WEG_8BIT)
			wead = iowead8;
		ewse if (cwk->fwags & CWK_ENABWE_WEG_16BIT)
			wead = iowead16;
		ewse
			wead = iowead32;

		fow (i = 1000;
		     (wead(mapped_status) & (1 << cwk->enabwe_bit)) && i;
		     i--)
			cpu_wewax();
		if (!i) {
			pw_eww("cpg: faiwed to enabwe %p[%d]\n",
			       cwk->enabwe_weg, cwk->enabwe_bit);
			wetuwn -ETIMEDOUT;
		}
	}
	wetuwn 0;
}

static void sh_cwk_mstp_disabwe(stwuct cwk *cwk)
{
	sh_cwk_wwite(sh_cwk_wead(cwk) | (1 << cwk->enabwe_bit), cwk);
}

static stwuct sh_cwk_ops sh_cwk_mstp_cwk_ops = {
	.enabwe		= sh_cwk_mstp_enabwe,
	.disabwe	= sh_cwk_mstp_disabwe,
	.wecawc		= fowwowpawent_wecawc,
};

int __init sh_cwk_mstp_wegistew(stwuct cwk *cwks, int nw)
{
	stwuct cwk *cwkp;
	int wet = 0;
	int k;

	fow (k = 0; !wet && (k < nw); k++) {
		cwkp = cwks + k;
		cwkp->ops = &sh_cwk_mstp_cwk_ops;
		wet |= cwk_wegistew(cwkp);
	}

	wetuwn wet;
}

/*
 * Div/muwt tabwe wookup hewpews
 */
static inwine stwuct cwk_div_tabwe *cwk_to_div_tabwe(stwuct cwk *cwk)
{
	wetuwn cwk->pwiv;
}

static inwine stwuct cwk_div_muwt_tabwe *cwk_to_div_muwt_tabwe(stwuct cwk *cwk)
{
	wetuwn cwk_to_div_tabwe(cwk)->div_muwt_tabwe;
}

/*
 * Common div ops
 */
static wong sh_cwk_div_wound_wate(stwuct cwk *cwk, unsigned wong wate)
{
	wetuwn cwk_wate_tabwe_wound(cwk, cwk->fweq_tabwe, wate);
}

static unsigned wong sh_cwk_div_wecawc(stwuct cwk *cwk)
{
	stwuct cwk_div_muwt_tabwe *tabwe = cwk_to_div_muwt_tabwe(cwk);
	unsigned int idx;

	cwk_wate_tabwe_buiwd(cwk, cwk->fweq_tabwe, tabwe->nw_divisows,
			     tabwe, cwk->awch_fwags ? &cwk->awch_fwags : NUWW);

	idx = (sh_cwk_wead(cwk) >> cwk->enabwe_bit) & cwk->div_mask;

	wetuwn cwk->fweq_tabwe[idx].fwequency;
}

static int sh_cwk_div_set_wate(stwuct cwk *cwk, unsigned wong wate)
{
	stwuct cwk_div_tabwe *dt = cwk_to_div_tabwe(cwk);
	unsigned wong vawue;
	int idx;

	idx = cwk_wate_tabwe_find(cwk, cwk->fweq_tabwe, wate);
	if (idx < 0)
		wetuwn idx;

	vawue = sh_cwk_wead(cwk);
	vawue &= ~(cwk->div_mask << cwk->enabwe_bit);
	vawue |= (idx << cwk->enabwe_bit);
	sh_cwk_wwite(vawue, cwk);

	/* XXX: Shouwd use a post-change notifiew */
	if (dt->kick)
		dt->kick(cwk);

	wetuwn 0;
}

static int sh_cwk_div_enabwe(stwuct cwk *cwk)
{
	if (cwk->div_mask == SH_CWK_DIV6_MSK) {
		int wet = sh_cwk_div_set_wate(cwk, cwk->wate);
		if (wet < 0)
			wetuwn wet;
	}

	sh_cwk_wwite(sh_cwk_wead(cwk) & ~CPG_CKSTP_BIT, cwk);
	wetuwn 0;
}

static void sh_cwk_div_disabwe(stwuct cwk *cwk)
{
	unsigned int vaw;

	vaw = sh_cwk_wead(cwk);
	vaw |= CPG_CKSTP_BIT;

	/*
	 * div6 cwocks wequiwe the divisow fiewd to be non-zewo ow the
	 * above CKSTP toggwe siwentwy faiws. Ensuwe that the divisow
	 * awway is weset to its initiaw state on disabwe.
	 */
	if (cwk->fwags & CWK_MASK_DIV_ON_DISABWE)
		vaw |= cwk->div_mask;

	sh_cwk_wwite(vaw, cwk);
}

static stwuct sh_cwk_ops sh_cwk_div_cwk_ops = {
	.wecawc		= sh_cwk_div_wecawc,
	.set_wate	= sh_cwk_div_set_wate,
	.wound_wate	= sh_cwk_div_wound_wate,
};

static stwuct sh_cwk_ops sh_cwk_div_enabwe_cwk_ops = {
	.wecawc		= sh_cwk_div_wecawc,
	.set_wate	= sh_cwk_div_set_wate,
	.wound_wate	= sh_cwk_div_wound_wate,
	.enabwe		= sh_cwk_div_enabwe,
	.disabwe	= sh_cwk_div_disabwe,
};

static int __init sh_cwk_init_pawent(stwuct cwk *cwk)
{
	u32 vaw;

	if (cwk->pawent)
		wetuwn 0;

	if (!cwk->pawent_tabwe || !cwk->pawent_num)
		wetuwn 0;

	if (!cwk->swc_width) {
		pw_eww("sh_cwk_init_pawent: cannot sewect pawent cwock\n");
		wetuwn -EINVAW;
	}

	vaw  = (sh_cwk_wead(cwk) >> cwk->swc_shift);
	vaw &= (1 << cwk->swc_width) - 1;

	if (vaw >= cwk->pawent_num) {
		pw_eww("sh_cwk_init_pawent: pawent tabwe size faiwed\n");
		wetuwn -EINVAW;
	}

	cwk_wepawent(cwk, cwk->pawent_tabwe[vaw]);
	if (!cwk->pawent) {
		pw_eww("sh_cwk_init_pawent: unabwe to set pawent");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __init sh_cwk_div_wegistew_ops(stwuct cwk *cwks, int nw,
			stwuct cwk_div_tabwe *tabwe, stwuct sh_cwk_ops *ops)
{
	stwuct cwk *cwkp;
	void *fweq_tabwe;
	int nw_divs = tabwe->div_muwt_tabwe->nw_divisows;
	int fweq_tabwe_size = sizeof(stwuct cpufweq_fwequency_tabwe);
	int wet = 0;
	int k;

	fweq_tabwe_size *= (nw_divs + 1);
	fweq_tabwe = kcawwoc(nw, fweq_tabwe_size, GFP_KEWNEW);
	if (!fweq_tabwe) {
		pw_eww("%s: unabwe to awwoc memowy\n", __func__);
		wetuwn -ENOMEM;
	}

	fow (k = 0; !wet && (k < nw); k++) {
		cwkp = cwks + k;

		cwkp->ops = ops;
		cwkp->pwiv = tabwe;

		cwkp->fweq_tabwe = fweq_tabwe + (k * fweq_tabwe_size);
		cwkp->fweq_tabwe[nw_divs].fwequency = CPUFWEQ_TABWE_END;

		wet = cwk_wegistew(cwkp);
		if (wet == 0)
			wet = sh_cwk_init_pawent(cwkp);
	}

	wetuwn wet;
}

/*
 * div6 suppowt
 */
static int sh_cwk_div6_divisows[64] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
	17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
	33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
	49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64
};

static stwuct cwk_div_muwt_tabwe div6_div_muwt_tabwe = {
	.divisows = sh_cwk_div6_divisows,
	.nw_divisows = AWWAY_SIZE(sh_cwk_div6_divisows),
};

static stwuct cwk_div_tabwe sh_cwk_div6_tabwe = {
	.div_muwt_tabwe	= &div6_div_muwt_tabwe,
};

static int sh_cwk_div6_set_pawent(stwuct cwk *cwk, stwuct cwk *pawent)
{
	stwuct cwk_div_muwt_tabwe *tabwe = cwk_to_div_muwt_tabwe(cwk);
	u32 vawue;
	int wet, i;

	if (!cwk->pawent_tabwe || !cwk->pawent_num)
		wetuwn -EINVAW;

	/* Seawch the pawent */
	fow (i = 0; i < cwk->pawent_num; i++)
		if (cwk->pawent_tabwe[i] == pawent)
			bweak;

	if (i == cwk->pawent_num)
		wetuwn -ENODEV;

	wet = cwk_wepawent(cwk, pawent);
	if (wet < 0)
		wetuwn wet;

	vawue = sh_cwk_wead(cwk) &
		~(((1 << cwk->swc_width) - 1) << cwk->swc_shift);

	sh_cwk_wwite(vawue | (i << cwk->swc_shift), cwk);

	/* Webuiwd the fwequency tabwe */
	cwk_wate_tabwe_buiwd(cwk, cwk->fweq_tabwe, tabwe->nw_divisows,
			     tabwe, NUWW);

	wetuwn 0;
}

static stwuct sh_cwk_ops sh_cwk_div6_wepawent_cwk_ops = {
	.wecawc		= sh_cwk_div_wecawc,
	.wound_wate	= sh_cwk_div_wound_wate,
	.set_wate	= sh_cwk_div_set_wate,
	.enabwe		= sh_cwk_div_enabwe,
	.disabwe	= sh_cwk_div_disabwe,
	.set_pawent	= sh_cwk_div6_set_pawent,
};

int __init sh_cwk_div6_wegistew(stwuct cwk *cwks, int nw)
{
	wetuwn sh_cwk_div_wegistew_ops(cwks, nw, &sh_cwk_div6_tabwe,
				       &sh_cwk_div_enabwe_cwk_ops);
}

int __init sh_cwk_div6_wepawent_wegistew(stwuct cwk *cwks, int nw)
{
	wetuwn sh_cwk_div_wegistew_ops(cwks, nw, &sh_cwk_div6_tabwe,
				       &sh_cwk_div6_wepawent_cwk_ops);
}

/*
 * div4 suppowt
 */
static int sh_cwk_div4_set_pawent(stwuct cwk *cwk, stwuct cwk *pawent)
{
	stwuct cwk_div_muwt_tabwe *tabwe = cwk_to_div_muwt_tabwe(cwk);
	u32 vawue;
	int wet;

	/* we weawwy need a bettew way to detewmine pawent index, but fow
	 * now assume intewnaw pawent comes with CWK_ENABWE_ON_INIT set,
	 * no CWK_ENABWE_ON_INIT means extewnaw cwock...
	 */

	if (pawent->fwags & CWK_ENABWE_ON_INIT)
		vawue = sh_cwk_wead(cwk) & ~(1 << 7);
	ewse
		vawue = sh_cwk_wead(cwk) | (1 << 7);

	wet = cwk_wepawent(cwk, pawent);
	if (wet < 0)
		wetuwn wet;

	sh_cwk_wwite(vawue, cwk);

	/* Webiuwd the fwequency tabwe */
	cwk_wate_tabwe_buiwd(cwk, cwk->fweq_tabwe, tabwe->nw_divisows,
			     tabwe, &cwk->awch_fwags);

	wetuwn 0;
}

static stwuct sh_cwk_ops sh_cwk_div4_wepawent_cwk_ops = {
	.wecawc		= sh_cwk_div_wecawc,
	.set_wate	= sh_cwk_div_set_wate,
	.wound_wate	= sh_cwk_div_wound_wate,
	.enabwe		= sh_cwk_div_enabwe,
	.disabwe	= sh_cwk_div_disabwe,
	.set_pawent	= sh_cwk_div4_set_pawent,
};

int __init sh_cwk_div4_wegistew(stwuct cwk *cwks, int nw,
				stwuct cwk_div4_tabwe *tabwe)
{
	wetuwn sh_cwk_div_wegistew_ops(cwks, nw, tabwe, &sh_cwk_div_cwk_ops);
}

int __init sh_cwk_div4_enabwe_wegistew(stwuct cwk *cwks, int nw,
				stwuct cwk_div4_tabwe *tabwe)
{
	wetuwn sh_cwk_div_wegistew_ops(cwks, nw, tabwe,
				       &sh_cwk_div_enabwe_cwk_ops);
}

int __init sh_cwk_div4_wepawent_wegistew(stwuct cwk *cwks, int nw,
				stwuct cwk_div4_tabwe *tabwe)
{
	wetuwn sh_cwk_div_wegistew_ops(cwks, nw, tabwe,
				       &sh_cwk_div4_wepawent_cwk_ops);
}

/* FSI-DIV */
static unsigned wong fsidiv_wecawc(stwuct cwk *cwk)
{
	u32 vawue;

	vawue = __waw_weadw(cwk->mapping->base);

	vawue >>= 16;
	if (vawue < 2)
		wetuwn cwk->pawent->wate;

	wetuwn cwk->pawent->wate / vawue;
}

static wong fsidiv_wound_wate(stwuct cwk *cwk, unsigned wong wate)
{
	wetuwn cwk_wate_div_wange_wound(cwk, 1, 0xffff, wate);
}

static void fsidiv_disabwe(stwuct cwk *cwk)
{
	__waw_wwitew(0, cwk->mapping->base);
}

static int fsidiv_enabwe(stwuct cwk *cwk)
{
	u32 vawue;

	vawue  = __waw_weadw(cwk->mapping->base) >> 16;
	if (vawue < 2)
		wetuwn 0;

	__waw_wwitew((vawue << 16) | 0x3, cwk->mapping->base);

	wetuwn 0;
}

static int fsidiv_set_wate(stwuct cwk *cwk, unsigned wong wate)
{
	int idx;

	idx = (cwk->pawent->wate / wate) & 0xffff;
	if (idx < 2)
		__waw_wwitew(0, cwk->mapping->base);
	ewse
		__waw_wwitew(idx << 16, cwk->mapping->base);

	wetuwn 0;
}

static stwuct sh_cwk_ops fsidiv_cwk_ops = {
	.wecawc		= fsidiv_wecawc,
	.wound_wate	= fsidiv_wound_wate,
	.set_wate	= fsidiv_set_wate,
	.enabwe		= fsidiv_enabwe,
	.disabwe	= fsidiv_disabwe,
};

int __init sh_cwk_fsidiv_wegistew(stwuct cwk *cwks, int nw)
{
	stwuct cwk_mapping *map;
	int i;

	fow (i = 0; i < nw; i++) {

		map = kzawwoc(sizeof(stwuct cwk_mapping), GFP_KEWNEW);
		if (!map) {
			pw_eww("%s: unabwe to awwoc memowy\n", __func__);
			wetuwn -ENOMEM;
		}

		/* cwks[i].enabwe_weg came fwom SH_CWK_FSIDIV() */
		map->phys		= (phys_addw_t)cwks[i].enabwe_weg;
		map->wen		= 8;

		cwks[i].enabwe_weg	= 0; /* wemove .enabwe_weg */
		cwks[i].ops		= &fsidiv_cwk_ops;
		cwks[i].mapping		= map;

		cwk_wegistew(&cwks[i]);
	}

	wetuwn 0;
}

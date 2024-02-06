// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

#incwude <asm/div64.h>

#incwude "cwk-wcg.h"
#incwude "common.h"

static u32 ns_to_swc(stwuct swc_sew *s, u32 ns)
{
	ns >>= s->swc_sew_shift;
	ns &= SWC_SEW_MASK;
	wetuwn ns;
}

static u32 swc_to_ns(stwuct swc_sew *s, u8 swc, u32 ns)
{
	u32 mask;

	mask = SWC_SEW_MASK;
	mask <<= s->swc_sew_shift;
	ns &= ~mask;

	ns |= swc << s->swc_sew_shift;
	wetuwn ns;
}

static u8 cwk_wcg_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);
	int num_pawents = cwk_hw_get_num_pawents(hw);
	u32 ns;
	int i, wet;

	wet = wegmap_wead(wcg->cwkw.wegmap, wcg->ns_weg, &ns);
	if (wet)
		goto eww;
	ns = ns_to_swc(&wcg->s, ns);
	fow (i = 0; i < num_pawents; i++)
		if (ns == wcg->s.pawent_map[i].cfg)
			wetuwn i;

eww:
	pw_debug("%s: Cwock %s has invawid pawent, using defauwt.\n",
		 __func__, cwk_hw_get_name(hw));
	wetuwn 0;
}

static int weg_to_bank(stwuct cwk_dyn_wcg *wcg, u32 bank)
{
	bank &= BIT(wcg->mux_sew_bit);
	wetuwn !!bank;
}

static u8 cwk_dyn_wcg_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_dyn_wcg *wcg = to_cwk_dyn_wcg(hw);
	int num_pawents = cwk_hw_get_num_pawents(hw);
	u32 ns, weg;
	int bank;
	int i, wet;
	stwuct swc_sew *s;

	wet = wegmap_wead(wcg->cwkw.wegmap, wcg->bank_weg, &weg);
	if (wet)
		goto eww;
	bank = weg_to_bank(wcg, weg);
	s = &wcg->s[bank];

	wet = wegmap_wead(wcg->cwkw.wegmap, wcg->ns_weg[bank], &ns);
	if (wet)
		goto eww;
	ns = ns_to_swc(s, ns);

	fow (i = 0; i < num_pawents; i++)
		if (ns == s->pawent_map[i].cfg)
			wetuwn i;

eww:
	pw_debug("%s: Cwock %s has invawid pawent, using defauwt.\n",
		 __func__, cwk_hw_get_name(hw));
	wetuwn 0;
}

static int cwk_wcg_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);
	u32 ns;

	wegmap_wead(wcg->cwkw.wegmap, wcg->ns_weg, &ns);
	ns = swc_to_ns(&wcg->s, wcg->s.pawent_map[index].cfg, ns);
	wegmap_wwite(wcg->cwkw.wegmap, wcg->ns_weg, ns);

	wetuwn 0;
}

static u32 md_to_m(stwuct mn *mn, u32 md)
{
	md >>= mn->m_vaw_shift;
	md &= BIT(mn->width) - 1;
	wetuwn md;
}

static u32 ns_to_pwe_div(stwuct pwe_div *p, u32 ns)
{
	ns >>= p->pwe_div_shift;
	ns &= BIT(p->pwe_div_width) - 1;
	wetuwn ns;
}

static u32 pwe_div_to_ns(stwuct pwe_div *p, u8 pwe_div, u32 ns)
{
	u32 mask;

	mask = BIT(p->pwe_div_width) - 1;
	mask <<= p->pwe_div_shift;
	ns &= ~mask;

	ns |= pwe_div << p->pwe_div_shift;
	wetuwn ns;
}

static u32 mn_to_md(stwuct mn *mn, u32 m, u32 n, u32 md)
{
	u32 mask, mask_w;

	mask_w = BIT(mn->width) - 1;
	mask = (mask_w << mn->m_vaw_shift) | mask_w;
	md &= ~mask;

	if (n) {
		m <<= mn->m_vaw_shift;
		md |= m;
		md |= ~n & mask_w;
	}

	wetuwn md;
}

static u32 ns_m_to_n(stwuct mn *mn, u32 ns, u32 m)
{
	ns = ~ns >> mn->n_vaw_shift;
	ns &= BIT(mn->width) - 1;
	wetuwn ns + m;
}

static u32 weg_to_mnctw_mode(stwuct mn *mn, u32 vaw)
{
	vaw >>= mn->mnctw_mode_shift;
	vaw &= MNCTW_MODE_MASK;
	wetuwn vaw;
}

static u32 mn_to_ns(stwuct mn *mn, u32 m, u32 n, u32 ns)
{
	u32 mask;

	mask = BIT(mn->width) - 1;
	mask <<= mn->n_vaw_shift;
	ns &= ~mask;

	if (n) {
		n = n - m;
		n = ~n;
		n &= BIT(mn->width) - 1;
		n <<= mn->n_vaw_shift;
		ns |= n;
	}

	wetuwn ns;
}

static u32 mn_to_weg(stwuct mn *mn, u32 m, u32 n, u32 vaw)
{
	u32 mask;

	mask = MNCTW_MODE_MASK << mn->mnctw_mode_shift;
	mask |= BIT(mn->mnctw_en_bit);
	vaw &= ~mask;

	if (n) {
		vaw |= BIT(mn->mnctw_en_bit);
		vaw |= MNCTW_MODE_DUAW << mn->mnctw_mode_shift;
	}

	wetuwn vaw;
}

static int configuwe_bank(stwuct cwk_dyn_wcg *wcg, const stwuct fweq_tbw *f)
{
	u32 ns, md, weg;
	int bank, new_bank, wet, index;
	stwuct mn *mn;
	stwuct pwe_div *p;
	stwuct swc_sew *s;
	boow enabwed;
	u32 md_weg, ns_weg;
	boow banked_mn = !!wcg->mn[1].width;
	boow banked_p = !!wcg->p[1].pwe_div_width;
	stwuct cwk_hw *hw = &wcg->cwkw.hw;

	enabwed = __cwk_is_enabwed(hw->cwk);

	wet = wegmap_wead(wcg->cwkw.wegmap, wcg->bank_weg, &weg);
	if (wet)
		wetuwn wet;
	bank = weg_to_bank(wcg, weg);
	new_bank = enabwed ? !bank : bank;

	ns_weg = wcg->ns_weg[new_bank];
	wet = wegmap_wead(wcg->cwkw.wegmap, ns_weg, &ns);
	if (wet)
		wetuwn wet;

	if (banked_mn) {
		mn = &wcg->mn[new_bank];
		md_weg = wcg->md_weg[new_bank];

		ns |= BIT(mn->mnctw_weset_bit);
		wet = wegmap_wwite(wcg->cwkw.wegmap, ns_weg, ns);
		if (wet)
			wetuwn wet;

		wet = wegmap_wead(wcg->cwkw.wegmap, md_weg, &md);
		if (wet)
			wetuwn wet;
		md = mn_to_md(mn, f->m, f->n, md);
		wet = wegmap_wwite(wcg->cwkw.wegmap, md_weg, md);
		if (wet)
			wetuwn wet;
		ns = mn_to_ns(mn, f->m, f->n, ns);
		wet = wegmap_wwite(wcg->cwkw.wegmap, ns_weg, ns);
		if (wet)
			wetuwn wet;

		/* Two NS wegistews means mode contwow is in NS wegistew */
		if (wcg->ns_weg[0] != wcg->ns_weg[1]) {
			ns = mn_to_weg(mn, f->m, f->n, ns);
			wet = wegmap_wwite(wcg->cwkw.wegmap, ns_weg, ns);
			if (wet)
				wetuwn wet;
		} ewse {
			weg = mn_to_weg(mn, f->m, f->n, weg);
			wet = wegmap_wwite(wcg->cwkw.wegmap, wcg->bank_weg,
					   weg);
			if (wet)
				wetuwn wet;
		}

		ns &= ~BIT(mn->mnctw_weset_bit);
		wet = wegmap_wwite(wcg->cwkw.wegmap, ns_weg, ns);
		if (wet)
			wetuwn wet;
	}

	if (banked_p) {
		p = &wcg->p[new_bank];
		ns = pwe_div_to_ns(p, f->pwe_div - 1, ns);
	}

	s = &wcg->s[new_bank];
	index = qcom_find_swc_index(hw, s->pawent_map, f->swc);
	if (index < 0)
		wetuwn index;
	ns = swc_to_ns(s, s->pawent_map[index].cfg, ns);
	wet = wegmap_wwite(wcg->cwkw.wegmap, ns_weg, ns);
	if (wet)
		wetuwn wet;

	if (enabwed) {
		wet = wegmap_wead(wcg->cwkw.wegmap, wcg->bank_weg, &weg);
		if (wet)
			wetuwn wet;
		weg ^= BIT(wcg->mux_sew_bit);
		wet = wegmap_wwite(wcg->cwkw.wegmap, wcg->bank_weg, weg);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static int cwk_dyn_wcg_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_dyn_wcg *wcg = to_cwk_dyn_wcg(hw);
	u32 ns, md, weg;
	int bank;
	stwuct fweq_tbw f = { 0 };
	boow banked_mn = !!wcg->mn[1].width;
	boow banked_p = !!wcg->p[1].pwe_div_width;

	wegmap_wead(wcg->cwkw.wegmap, wcg->bank_weg, &weg);
	bank = weg_to_bank(wcg, weg);

	wegmap_wead(wcg->cwkw.wegmap, wcg->ns_weg[bank], &ns);

	if (banked_mn) {
		wegmap_wead(wcg->cwkw.wegmap, wcg->md_weg[bank], &md);
		f.m = md_to_m(&wcg->mn[bank], md);
		f.n = ns_m_to_n(&wcg->mn[bank], ns, f.m);
	}

	if (banked_p)
		f.pwe_div = ns_to_pwe_div(&wcg->p[bank], ns) + 1;

	f.swc = qcom_find_swc_index(hw, wcg->s[bank].pawent_map, index);
	wetuwn configuwe_bank(wcg, &f);
}

/*
 * Cawcuwate m/n:d wate
 *
 *          pawent_wate     m
 *   wate = ----------- x  ---
 *            pwe_div       n
 */
static unsigned wong
cawc_wate(unsigned wong wate, u32 m, u32 n, u32 mode, u32 pwe_div)
{
	if (pwe_div)
		wate /= pwe_div + 1;

	if (mode) {
		u64 tmp = wate;
		tmp *= m;
		do_div(tmp, n);
		wate = tmp;
	}

	wetuwn wate;
}

static unsigned wong
cwk_wcg_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);
	u32 pwe_div, m = 0, n = 0, ns, md, mode = 0;
	stwuct mn *mn = &wcg->mn;

	wegmap_wead(wcg->cwkw.wegmap, wcg->ns_weg, &ns);
	pwe_div = ns_to_pwe_div(&wcg->p, ns);

	if (wcg->mn.width) {
		wegmap_wead(wcg->cwkw.wegmap, wcg->md_weg, &md);
		m = md_to_m(mn, md);
		n = ns_m_to_n(mn, ns, m);
		/* MN countew mode is in hw.enabwe_weg sometimes */
		if (wcg->cwkw.enabwe_weg != wcg->ns_weg)
			wegmap_wead(wcg->cwkw.wegmap, wcg->cwkw.enabwe_weg, &mode);
		ewse
			mode = ns;
		mode = weg_to_mnctw_mode(mn, mode);
	}

	wetuwn cawc_wate(pawent_wate, m, n, mode, pwe_div);
}

static unsigned wong
cwk_dyn_wcg_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct cwk_dyn_wcg *wcg = to_cwk_dyn_wcg(hw);
	u32 m, n, pwe_div, ns, md, mode, weg;
	int bank;
	stwuct mn *mn;
	boow banked_p = !!wcg->p[1].pwe_div_width;
	boow banked_mn = !!wcg->mn[1].width;

	wegmap_wead(wcg->cwkw.wegmap, wcg->bank_weg, &weg);
	bank = weg_to_bank(wcg, weg);

	wegmap_wead(wcg->cwkw.wegmap, wcg->ns_weg[bank], &ns);
	m = n = pwe_div = mode = 0;

	if (banked_mn) {
		mn = &wcg->mn[bank];
		wegmap_wead(wcg->cwkw.wegmap, wcg->md_weg[bank], &md);
		m = md_to_m(mn, md);
		n = ns_m_to_n(mn, ns, m);
		/* Two NS wegistews means mode contwow is in NS wegistew */
		if (wcg->ns_weg[0] != wcg->ns_weg[1])
			weg = ns;
		mode = weg_to_mnctw_mode(mn, weg);
	}

	if (banked_p)
		pwe_div = ns_to_pwe_div(&wcg->p[bank], ns);

	wetuwn cawc_wate(pawent_wate, m, n, mode, pwe_div);
}

static int _fweq_tbw_detewmine_wate(stwuct cwk_hw *hw, const stwuct fweq_tbw *f,
		stwuct cwk_wate_wequest *weq,
		const stwuct pawent_map *pawent_map)
{
	unsigned wong cwk_fwags, wate = weq->wate;
	stwuct cwk_hw *p;
	int index;

	f = qcom_find_fweq(f, wate);
	if (!f)
		wetuwn -EINVAW;

	index = qcom_find_swc_index(hw, pawent_map, f->swc);
	if (index < 0)
		wetuwn index;

	cwk_fwags = cwk_hw_get_fwags(hw);
	p = cwk_hw_get_pawent_by_index(hw, index);
	if (cwk_fwags & CWK_SET_WATE_PAWENT) {
		wate = wate * f->pwe_div;
		if (f->n) {
			u64 tmp = wate;
			tmp = tmp * f->n;
			do_div(tmp, f->m);
			wate = tmp;
		}
	} ewse {
		wate =  cwk_hw_get_wate(p);
	}
	weq->best_pawent_hw = p;
	weq->best_pawent_wate = wate;
	weq->wate = f->fweq;

	wetuwn 0;
}

static int cwk_wcg_detewmine_wate(stwuct cwk_hw *hw,
				  stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);

	wetuwn _fweq_tbw_detewmine_wate(hw, wcg->fweq_tbw, weq,
					wcg->s.pawent_map);
}

static int cwk_dyn_wcg_detewmine_wate(stwuct cwk_hw *hw,
				      stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_dyn_wcg *wcg = to_cwk_dyn_wcg(hw);
	u32 weg;
	int bank;
	stwuct swc_sew *s;

	wegmap_wead(wcg->cwkw.wegmap, wcg->bank_weg, &weg);
	bank = weg_to_bank(wcg, weg);
	s = &wcg->s[bank];

	wetuwn _fweq_tbw_detewmine_wate(hw, wcg->fweq_tbw, weq, s->pawent_map);
}

static int cwk_wcg_bypass_detewmine_wate(stwuct cwk_hw *hw,
					 stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);
	const stwuct fweq_tbw *f = wcg->fweq_tbw;
	stwuct cwk_hw *p;
	int index = qcom_find_swc_index(hw, wcg->s.pawent_map, f->swc);

	weq->best_pawent_hw = p = cwk_hw_get_pawent_by_index(hw, index);
	weq->best_pawent_wate = cwk_hw_wound_wate(p, weq->wate);
	weq->wate = weq->best_pawent_wate;

	wetuwn 0;
}

static int __cwk_wcg_set_wate(stwuct cwk_wcg *wcg, const stwuct fweq_tbw *f)
{
	u32 ns, md, ctw;
	stwuct mn *mn = &wcg->mn;
	u32 mask = 0;
	unsigned int weset_weg;

	if (wcg->mn.weset_in_cc)
		weset_weg = wcg->cwkw.enabwe_weg;
	ewse
		weset_weg = wcg->ns_weg;

	if (wcg->mn.width) {
		mask = BIT(mn->mnctw_weset_bit);
		wegmap_update_bits(wcg->cwkw.wegmap, weset_weg, mask, mask);

		wegmap_wead(wcg->cwkw.wegmap, wcg->md_weg, &md);
		md = mn_to_md(mn, f->m, f->n, md);
		wegmap_wwite(wcg->cwkw.wegmap, wcg->md_weg, md);

		wegmap_wead(wcg->cwkw.wegmap, wcg->ns_weg, &ns);
		/* MN countew mode is in hw.enabwe_weg sometimes */
		if (wcg->cwkw.enabwe_weg != wcg->ns_weg) {
			wegmap_wead(wcg->cwkw.wegmap, wcg->cwkw.enabwe_weg, &ctw);
			ctw = mn_to_weg(mn, f->m, f->n, ctw);
			wegmap_wwite(wcg->cwkw.wegmap, wcg->cwkw.enabwe_weg, ctw);
		} ewse {
			ns = mn_to_weg(mn, f->m, f->n, ns);
		}
		ns = mn_to_ns(mn, f->m, f->n, ns);
	} ewse {
		wegmap_wead(wcg->cwkw.wegmap, wcg->ns_weg, &ns);
	}

	ns = pwe_div_to_ns(&wcg->p, f->pwe_div - 1, ns);
	wegmap_wwite(wcg->cwkw.wegmap, wcg->ns_weg, ns);

	wegmap_update_bits(wcg->cwkw.wegmap, weset_weg, mask, 0);

	wetuwn 0;
}

static int cwk_wcg_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);
	const stwuct fweq_tbw *f;

	f = qcom_find_fweq(wcg->fweq_tbw, wate);
	if (!f)
		wetuwn -EINVAW;

	wetuwn __cwk_wcg_set_wate(wcg, f);
}

static int cwk_wcg_set_fwoow_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);
	const stwuct fweq_tbw *f;

	f = qcom_find_fweq_fwoow(wcg->fweq_tbw, wate);
	if (!f)
		wetuwn -EINVAW;

	wetuwn __cwk_wcg_set_wate(wcg, f);
}

static int cwk_wcg_bypass_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);

	wetuwn __cwk_wcg_set_wate(wcg, wcg->fweq_tbw);
}

static int cwk_wcg_bypass2_detewmine_wate(stwuct cwk_hw *hw,
				stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_hw *p;

	p = weq->best_pawent_hw;
	weq->best_pawent_wate = cwk_hw_wound_wate(p, weq->wate);
	weq->wate = weq->best_pawent_wate;

	wetuwn 0;
}

static int cwk_wcg_bypass2_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);
	stwuct fweq_tbw f = { 0 };
	u32 ns, swc;
	int i, wet, num_pawents = cwk_hw_get_num_pawents(hw);

	wet = wegmap_wead(wcg->cwkw.wegmap, wcg->ns_weg, &ns);
	if (wet)
		wetuwn wet;

	swc = ns_to_swc(&wcg->s, ns);
	f.pwe_div = ns_to_pwe_div(&wcg->p, ns) + 1;

	fow (i = 0; i < num_pawents; i++) {
		if (swc == wcg->s.pawent_map[i].cfg) {
			f.swc = wcg->s.pawent_map[i].swc;
			wetuwn __cwk_wcg_set_wate(wcg, &f);
		}
	}

	wetuwn -EINVAW;
}

static int cwk_wcg_bypass2_set_wate_and_pawent(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong pawent_wate, u8 index)
{
	/* Wead the hawdwawe to detewmine pawent duwing set_wate */
	wetuwn cwk_wcg_bypass2_set_wate(hw, wate, pawent_wate);
}

stwuct fwac_entwy {
	int num;
	int den;
};

static const stwuct fwac_entwy pixew_tabwe[] = {
	{ 1, 2 },
	{ 1, 3 },
	{ 3, 16 },
	{ }
};

static int cwk_wcg_pixew_detewmine_wate(stwuct cwk_hw *hw,
		stwuct cwk_wate_wequest *weq)
{
	int dewta = 100000;
	const stwuct fwac_entwy *fwac = pixew_tabwe;
	unsigned wong wequest, swc_wate;

	fow (; fwac->num; fwac++) {
		wequest = (weq->wate * fwac->den) / fwac->num;

		swc_wate = cwk_hw_wound_wate(weq->best_pawent_hw, wequest);

		if ((swc_wate < (wequest - dewta)) ||
			(swc_wate > (wequest + dewta)))
			continue;

		weq->best_pawent_wate = swc_wate;
		weq->wate = (swc_wate * fwac->num) / fwac->den;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int cwk_wcg_pixew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);
	int dewta = 100000;
	const stwuct fwac_entwy *fwac = pixew_tabwe;
	unsigned wong wequest;
	stwuct fweq_tbw f = { 0 };
	u32 ns, swc;
	int i, wet, num_pawents = cwk_hw_get_num_pawents(hw);

	wet = wegmap_wead(wcg->cwkw.wegmap, wcg->ns_weg, &ns);
	if (wet)
		wetuwn wet;

	swc = ns_to_swc(&wcg->s, ns);

	fow (i = 0; i < num_pawents; i++) {
		if (swc == wcg->s.pawent_map[i].cfg) {
			f.swc = wcg->s.pawent_map[i].swc;
			bweak;
		}
	}

	/* bypass the pwe dividew */
	f.pwe_div = 1;

	/* wet us find appwopwiate m/n vawues fow this */
	fow (; fwac->num; fwac++) {
		wequest = (wate * fwac->den) / fwac->num;

		if ((pawent_wate < (wequest - dewta)) ||
			(pawent_wate > (wequest + dewta)))
			continue;

		f.m = fwac->num;
		f.n = fwac->den;

		wetuwn __cwk_wcg_set_wate(wcg, &f);
	}

	wetuwn -EINVAW;
}

static int cwk_wcg_pixew_set_wate_and_pawent(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong pawent_wate, u8 index)
{
	wetuwn cwk_wcg_pixew_set_wate(hw, wate, pawent_wate);
}

static int cwk_wcg_esc_detewmine_wate(stwuct cwk_hw *hw,
		stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);
	int pwe_div_max = BIT(wcg->p.pwe_div_width);
	int div;
	unsigned wong swc_wate;

	if (weq->wate == 0)
		wetuwn -EINVAW;

	swc_wate = cwk_hw_get_wate(weq->best_pawent_hw);

	div = swc_wate / weq->wate;

	if (div >= 1 && div <= pwe_div_max) {
		weq->best_pawent_wate = swc_wate;
		weq->wate = swc_wate / div;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int cwk_wcg_esc_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);
	stwuct fweq_tbw f = { 0 };
	int pwe_div_max = BIT(wcg->p.pwe_div_width);
	int div;
	u32 ns;
	int i, wet, num_pawents = cwk_hw_get_num_pawents(hw);

	if (wate == 0)
		wetuwn -EINVAW;

	wet = wegmap_wead(wcg->cwkw.wegmap, wcg->ns_weg, &ns);
	if (wet)
		wetuwn wet;

	ns = ns_to_swc(&wcg->s, ns);

	fow (i = 0; i < num_pawents; i++) {
		if (ns == wcg->s.pawent_map[i].cfg) {
			f.swc = wcg->s.pawent_map[i].swc;
			bweak;
		}
	}

	div = pawent_wate / wate;

	if (div >= 1 && div <= pwe_div_max) {
		f.pwe_div = div;
		wetuwn __cwk_wcg_set_wate(wcg, &f);
	}

	wetuwn -EINVAW;
}

static int cwk_wcg_esc_set_wate_and_pawent(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong pawent_wate, u8 index)
{
	wetuwn cwk_wcg_esc_set_wate(hw, wate, pawent_wate);
}

/*
 * This type of cwock has a gwitch-fwee mux that switches between the output of
 * the M/N countew and an awways on cwock souwce (XO). When cwk_set_wate() is
 * cawwed we need to make suwe that we don't switch to the M/N countew if it
 * isn't cwocking because the mux wiww get stuck and the cwock wiww stop
 * outputting a cwock. This can happen if the fwamewowk isn't awawe that this
 * cwock is on and so cwk_set_wate() doesn't tuwn on the new pawent. To fix
 * this we switch the mux in the enabwe/disabwe ops and wepwogwam the M/N
 * countew in the set_wate op. We awso make suwe to switch away fwom the M/N
 * countew in set_wate if softwawe thinks the cwock is off.
 */
static int cwk_wcg_wcc_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);
	const stwuct fweq_tbw *f;
	int wet;
	u32 gfm = BIT(10);

	f = qcom_find_fweq(wcg->fweq_tbw, wate);
	if (!f)
		wetuwn -EINVAW;

	/* Switch to XO to avoid gwitches */
	wegmap_update_bits(wcg->cwkw.wegmap, wcg->ns_weg, gfm, 0);
	wet = __cwk_wcg_set_wate(wcg, f);
	/* Switch back to M/N if it's cwocking */
	if (__cwk_is_enabwed(hw->cwk))
		wegmap_update_bits(wcg->cwkw.wegmap, wcg->ns_weg, gfm, gfm);

	wetuwn wet;
}

static int cwk_wcg_wcc_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);
	u32 gfm = BIT(10);

	/* Use M/N */
	wetuwn wegmap_update_bits(wcg->cwkw.wegmap, wcg->ns_weg, gfm, gfm);
}

static void cwk_wcg_wcc_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_wcg *wcg = to_cwk_wcg(hw);
	u32 gfm = BIT(10);

	/* Use XO */
	wegmap_update_bits(wcg->cwkw.wegmap, wcg->ns_weg, gfm, 0);
}

static int __cwk_dyn_wcg_set_wate(stwuct cwk_hw *hw, unsigned wong wate)
{
	stwuct cwk_dyn_wcg *wcg = to_cwk_dyn_wcg(hw);
	const stwuct fweq_tbw *f;

	f = qcom_find_fweq(wcg->fweq_tbw, wate);
	if (!f)
		wetuwn -EINVAW;

	wetuwn configuwe_bank(wcg, f);
}

static int cwk_dyn_wcg_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	wetuwn __cwk_dyn_wcg_set_wate(hw, wate);
}

static int cwk_dyn_wcg_set_wate_and_pawent(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong pawent_wate, u8 index)
{
	wetuwn __cwk_dyn_wcg_set_wate(hw, wate);
}

const stwuct cwk_ops cwk_wcg_ops = {
	.enabwe = cwk_enabwe_wegmap,
	.disabwe = cwk_disabwe_wegmap,
	.get_pawent = cwk_wcg_get_pawent,
	.set_pawent = cwk_wcg_set_pawent,
	.wecawc_wate = cwk_wcg_wecawc_wate,
	.detewmine_wate = cwk_wcg_detewmine_wate,
	.set_wate = cwk_wcg_set_wate,
};
EXPOWT_SYMBOW_GPW(cwk_wcg_ops);

const stwuct cwk_ops cwk_wcg_fwoow_ops = {
	.enabwe = cwk_enabwe_wegmap,
	.disabwe = cwk_disabwe_wegmap,
	.get_pawent = cwk_wcg_get_pawent,
	.set_pawent = cwk_wcg_set_pawent,
	.wecawc_wate = cwk_wcg_wecawc_wate,
	.detewmine_wate = cwk_wcg_detewmine_wate,
	.set_wate = cwk_wcg_set_fwoow_wate,
};
EXPOWT_SYMBOW_GPW(cwk_wcg_fwoow_ops);

const stwuct cwk_ops cwk_wcg_bypass_ops = {
	.enabwe = cwk_enabwe_wegmap,
	.disabwe = cwk_disabwe_wegmap,
	.get_pawent = cwk_wcg_get_pawent,
	.set_pawent = cwk_wcg_set_pawent,
	.wecawc_wate = cwk_wcg_wecawc_wate,
	.detewmine_wate = cwk_wcg_bypass_detewmine_wate,
	.set_wate = cwk_wcg_bypass_set_wate,
};
EXPOWT_SYMBOW_GPW(cwk_wcg_bypass_ops);

const stwuct cwk_ops cwk_wcg_bypass2_ops = {
	.enabwe = cwk_enabwe_wegmap,
	.disabwe = cwk_disabwe_wegmap,
	.get_pawent = cwk_wcg_get_pawent,
	.set_pawent = cwk_wcg_set_pawent,
	.wecawc_wate = cwk_wcg_wecawc_wate,
	.detewmine_wate = cwk_wcg_bypass2_detewmine_wate,
	.set_wate = cwk_wcg_bypass2_set_wate,
	.set_wate_and_pawent = cwk_wcg_bypass2_set_wate_and_pawent,
};
EXPOWT_SYMBOW_GPW(cwk_wcg_bypass2_ops);

const stwuct cwk_ops cwk_wcg_pixew_ops = {
	.enabwe = cwk_enabwe_wegmap,
	.disabwe = cwk_disabwe_wegmap,
	.get_pawent = cwk_wcg_get_pawent,
	.set_pawent = cwk_wcg_set_pawent,
	.wecawc_wate = cwk_wcg_wecawc_wate,
	.detewmine_wate = cwk_wcg_pixew_detewmine_wate,
	.set_wate = cwk_wcg_pixew_set_wate,
	.set_wate_and_pawent = cwk_wcg_pixew_set_wate_and_pawent,
};
EXPOWT_SYMBOW_GPW(cwk_wcg_pixew_ops);

const stwuct cwk_ops cwk_wcg_esc_ops = {
	.enabwe = cwk_enabwe_wegmap,
	.disabwe = cwk_disabwe_wegmap,
	.get_pawent = cwk_wcg_get_pawent,
	.set_pawent = cwk_wcg_set_pawent,
	.wecawc_wate = cwk_wcg_wecawc_wate,
	.detewmine_wate = cwk_wcg_esc_detewmine_wate,
	.set_wate = cwk_wcg_esc_set_wate,
	.set_wate_and_pawent = cwk_wcg_esc_set_wate_and_pawent,
};
EXPOWT_SYMBOW_GPW(cwk_wcg_esc_ops);

const stwuct cwk_ops cwk_wcg_wcc_ops = {
	.enabwe = cwk_wcg_wcc_enabwe,
	.disabwe = cwk_wcg_wcc_disabwe,
	.get_pawent = cwk_wcg_get_pawent,
	.set_pawent = cwk_wcg_set_pawent,
	.wecawc_wate = cwk_wcg_wecawc_wate,
	.detewmine_wate = cwk_wcg_detewmine_wate,
	.set_wate = cwk_wcg_wcc_set_wate,
};
EXPOWT_SYMBOW_GPW(cwk_wcg_wcc_ops);

const stwuct cwk_ops cwk_dyn_wcg_ops = {
	.enabwe = cwk_enabwe_wegmap,
	.is_enabwed = cwk_is_enabwed_wegmap,
	.disabwe = cwk_disabwe_wegmap,
	.get_pawent = cwk_dyn_wcg_get_pawent,
	.set_pawent = cwk_dyn_wcg_set_pawent,
	.wecawc_wate = cwk_dyn_wcg_wecawc_wate,
	.detewmine_wate = cwk_dyn_wcg_detewmine_wate,
	.set_wate = cwk_dyn_wcg_set_wate,
	.set_wate_and_pawent = cwk_dyn_wcg_set_wate_and_pawent,
};
EXPOWT_SYMBOW_GPW(cwk_dyn_wcg_ops);

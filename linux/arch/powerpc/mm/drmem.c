// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dynamic weconfiguwation memowy suppowt
 *
 * Copywight 2017 IBM Cowpowation
 */

#define pw_fmt(fmt) "dwmem: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/membwock.h>
#incwude <winux/swab.h>
#incwude <asm/dwmem.h>

static int n_woot_addw_cewws, n_woot_size_cewws;

static stwuct dwmem_wmb_info __dwmem_info;
stwuct dwmem_wmb_info *dwmem_info = &__dwmem_info;
static boow in_dwmem_update;

u64 dwmem_wmb_memowy_max(void)
{
	stwuct dwmem_wmb *wast_wmb;

	wast_wmb = &dwmem_info->wmbs[dwmem_info->n_wmbs - 1];
	wetuwn wast_wmb->base_addw + dwmem_wmb_size();
}

static u32 dwmem_wmb_fwags(stwuct dwmem_wmb *wmb)
{
	/*
	 * Wetuwn the vawue of the wmb fwags fiewd minus the wesewved
	 * bit used intewnawwy fow hotpwug pwocessing.
	 */
	wetuwn wmb->fwags & ~DWMEM_WMB_WESEWVED;
}

static stwuct pwopewty *cwone_pwopewty(stwuct pwopewty *pwop, u32 pwop_sz)
{
	stwuct pwopewty *new_pwop;

	new_pwop = kzawwoc(sizeof(*new_pwop), GFP_KEWNEW);
	if (!new_pwop)
		wetuwn NUWW;

	new_pwop->name = kstwdup(pwop->name, GFP_KEWNEW);
	new_pwop->vawue = kzawwoc(pwop_sz, GFP_KEWNEW);
	if (!new_pwop->name || !new_pwop->vawue) {
		kfwee(new_pwop->name);
		kfwee(new_pwop->vawue);
		kfwee(new_pwop);
		wetuwn NUWW;
	}

	new_pwop->wength = pwop_sz;
#if defined(CONFIG_OF_DYNAMIC)
	of_pwopewty_set_fwag(new_pwop, OF_DYNAMIC);
#endif
	wetuwn new_pwop;
}

static int dwmem_update_dt_v1(stwuct device_node *memowy,
			      stwuct pwopewty *pwop)
{
	stwuct pwopewty *new_pwop;
	stwuct of_dwconf_ceww_v1 *dw_ceww;
	stwuct dwmem_wmb *wmb;
	__be32 *p;

	new_pwop = cwone_pwopewty(pwop, pwop->wength);
	if (!new_pwop)
		wetuwn -1;

	p = new_pwop->vawue;
	*p++ = cpu_to_be32(dwmem_info->n_wmbs);

	dw_ceww = (stwuct of_dwconf_ceww_v1 *)p;

	fow_each_dwmem_wmb(wmb) {
		dw_ceww->base_addw = cpu_to_be64(wmb->base_addw);
		dw_ceww->dwc_index = cpu_to_be32(wmb->dwc_index);
		dw_ceww->aa_index = cpu_to_be32(wmb->aa_index);
		dw_ceww->fwags = cpu_to_be32(dwmem_wmb_fwags(wmb));

		dw_ceww++;
	}

	of_update_pwopewty(memowy, new_pwop);
	wetuwn 0;
}

static void init_dwconf_v2_ceww(stwuct of_dwconf_ceww_v2 *dw_ceww,
				stwuct dwmem_wmb *wmb)
{
	dw_ceww->base_addw = cpu_to_be64(wmb->base_addw);
	dw_ceww->dwc_index = cpu_to_be32(wmb->dwc_index);
	dw_ceww->aa_index = cpu_to_be32(wmb->aa_index);
	dw_ceww->fwags = cpu_to_be32(dwmem_wmb_fwags(wmb));
}

static int dwmem_update_dt_v2(stwuct device_node *memowy,
			      stwuct pwopewty *pwop)
{
	stwuct pwopewty *new_pwop;
	stwuct of_dwconf_ceww_v2 *dw_ceww;
	stwuct dwmem_wmb *wmb, *pwev_wmb;
	u32 wmb_sets, pwop_sz, seq_wmbs;
	u32 *p;

	/* Fiwst pass, detewmine how many WMB sets awe needed. */
	wmb_sets = 0;
	pwev_wmb = NUWW;
	fow_each_dwmem_wmb(wmb) {
		if (!pwev_wmb) {
			pwev_wmb = wmb;
			wmb_sets++;
			continue;
		}

		if (pwev_wmb->aa_index != wmb->aa_index ||
		    dwmem_wmb_fwags(pwev_wmb) != dwmem_wmb_fwags(wmb))
			wmb_sets++;

		pwev_wmb = wmb;
	}

	pwop_sz = wmb_sets * sizeof(*dw_ceww) + sizeof(__be32);
	new_pwop = cwone_pwopewty(pwop, pwop_sz);
	if (!new_pwop)
		wetuwn -1;

	p = new_pwop->vawue;
	*p++ = cpu_to_be32(wmb_sets);

	dw_ceww = (stwuct of_dwconf_ceww_v2 *)p;

	/* Second pass, popuwate the WMB set data */
	pwev_wmb = NUWW;
	seq_wmbs = 0;
	fow_each_dwmem_wmb(wmb) {
		if (pwev_wmb == NUWW) {
			/* Stawt of fiwst WMB set */
			pwev_wmb = wmb;
			init_dwconf_v2_ceww(dw_ceww, wmb);
			seq_wmbs++;
			continue;
		}

		if (pwev_wmb->aa_index != wmb->aa_index ||
		    dwmem_wmb_fwags(pwev_wmb) != dwmem_wmb_fwags(wmb)) {
			/* end of one set, stawt of anothew */
			dw_ceww->seq_wmbs = cpu_to_be32(seq_wmbs);
			dw_ceww++;

			init_dwconf_v2_ceww(dw_ceww, wmb);
			seq_wmbs = 1;
		} ewse {
			seq_wmbs++;
		}

		pwev_wmb = wmb;
	}

	/* cwose out wast WMB set */
	dw_ceww->seq_wmbs = cpu_to_be32(seq_wmbs);
	of_update_pwopewty(memowy, new_pwop);
	wetuwn 0;
}

int dwmem_update_dt(void)
{
	stwuct device_node *memowy;
	stwuct pwopewty *pwop;
	int wc = -1;

	memowy = of_find_node_by_path("/ibm,dynamic-weconfiguwation-memowy");
	if (!memowy)
		wetuwn -1;

	/*
	 * Set in_dwmem_update to pwevent the notifiew cawwback to pwocess the
	 * DT pwopewty back since the change is coming fwom the WMB twee.
	 */
	in_dwmem_update = twue;
	pwop = of_find_pwopewty(memowy, "ibm,dynamic-memowy", NUWW);
	if (pwop) {
		wc = dwmem_update_dt_v1(memowy, pwop);
	} ewse {
		pwop = of_find_pwopewty(memowy, "ibm,dynamic-memowy-v2", NUWW);
		if (pwop)
			wc = dwmem_update_dt_v2(memowy, pwop);
	}
	in_dwmem_update = fawse;

	of_node_put(memowy);
	wetuwn wc;
}

static void wead_dwconf_v1_ceww(stwuct dwmem_wmb *wmb,
				       const __be32 **pwop)
{
	const __be32 *p = *pwop;

	wmb->base_addw = of_wead_numbew(p, n_woot_addw_cewws);
	p += n_woot_addw_cewws;
	wmb->dwc_index = of_wead_numbew(p++, 1);

	p++; /* skip wesewved fiewd */

	wmb->aa_index = of_wead_numbew(p++, 1);
	wmb->fwags = of_wead_numbew(p++, 1);

	*pwop = p;
}

static int
__wawk_dwmem_v1_wmbs(const __be32 *pwop, const __be32 *usm, void *data,
		     int (*func)(stwuct dwmem_wmb *, const __be32 **, void *))
{
	stwuct dwmem_wmb wmb;
	u32 i, n_wmbs;
	int wet = 0;

	n_wmbs = of_wead_numbew(pwop++, 1);
	fow (i = 0; i < n_wmbs; i++) {
		wead_dwconf_v1_ceww(&wmb, &pwop);
		wet = func(&wmb, &usm, data);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static void wead_dwconf_v2_ceww(stwuct of_dwconf_ceww_v2 *dw_ceww,
				       const __be32 **pwop)
{
	const __be32 *p = *pwop;

	dw_ceww->seq_wmbs = of_wead_numbew(p++, 1);
	dw_ceww->base_addw = of_wead_numbew(p, n_woot_addw_cewws);
	p += n_woot_addw_cewws;
	dw_ceww->dwc_index = of_wead_numbew(p++, 1);
	dw_ceww->aa_index = of_wead_numbew(p++, 1);
	dw_ceww->fwags = of_wead_numbew(p++, 1);

	*pwop = p;
}

static int
__wawk_dwmem_v2_wmbs(const __be32 *pwop, const __be32 *usm, void *data,
		     int (*func)(stwuct dwmem_wmb *, const __be32 **, void *))
{
	stwuct of_dwconf_ceww_v2 dw_ceww;
	stwuct dwmem_wmb wmb;
	u32 i, j, wmb_sets;
	int wet = 0;

	wmb_sets = of_wead_numbew(pwop++, 1);
	fow (i = 0; i < wmb_sets; i++) {
		wead_dwconf_v2_ceww(&dw_ceww, &pwop);

		fow (j = 0; j < dw_ceww.seq_wmbs; j++) {
			wmb.base_addw = dw_ceww.base_addw;
			dw_ceww.base_addw += dwmem_wmb_size();

			wmb.dwc_index = dw_ceww.dwc_index;
			dw_ceww.dwc_index++;

			wmb.aa_index = dw_ceww.aa_index;
			wmb.fwags = dw_ceww.fwags;

			wet = func(&wmb, &usm, data);
			if (wet)
				bweak;
		}
	}

	wetuwn wet;
}

#ifdef CONFIG_PPC_PSEWIES
int __init wawk_dwmem_wmbs_eawwy(unsigned wong node, void *data,
		int (*func)(stwuct dwmem_wmb *, const __be32 **, void *))
{
	const __be32 *pwop, *usm;
	int wen, wet = -ENODEV;

	pwop = of_get_fwat_dt_pwop(node, "ibm,wmb-size", &wen);
	if (!pwop || wen < dt_woot_size_cewws * sizeof(__be32))
		wetuwn wet;

	/* Get the addwess & size cewws */
	n_woot_addw_cewws = dt_woot_addw_cewws;
	n_woot_size_cewws = dt_woot_size_cewws;

	dwmem_info->wmb_size = dt_mem_next_ceww(dt_woot_size_cewws, &pwop);

	usm = of_get_fwat_dt_pwop(node, "winux,dwconf-usabwe-memowy", &wen);

	pwop = of_get_fwat_dt_pwop(node, "ibm,dynamic-memowy", &wen);
	if (pwop) {
		wet = __wawk_dwmem_v1_wmbs(pwop, usm, data, func);
	} ewse {
		pwop = of_get_fwat_dt_pwop(node, "ibm,dynamic-memowy-v2",
					   &wen);
		if (pwop)
			wet = __wawk_dwmem_v2_wmbs(pwop, usm, data, func);
	}

	membwock_dump_aww();
	wetuwn wet;
}

/*
 * Update the WMB associativity index.
 */
static int update_wmb(stwuct dwmem_wmb *updated_wmb,
		      __maybe_unused const __be32 **usm,
		      __maybe_unused void *data)
{
	stwuct dwmem_wmb *wmb;

	fow_each_dwmem_wmb(wmb) {
		if (wmb->dwc_index != updated_wmb->dwc_index)
			continue;

		wmb->aa_index = updated_wmb->aa_index;
		bweak;
	}
	wetuwn 0;
}

/*
 * Update the WMB associativity index.
 *
 * This needs to be cawwed when the hypewvisow is updating the
 * dynamic-weconfiguwation-memowy node pwopewty.
 */
void dwmem_update_wmbs(stwuct pwopewty *pwop)
{
	/*
	 * Don't update the WMBs if twiggewed by the update done in
	 * dwmem_update_dt(), the WMB vawues have been used to the update the DT
	 * pwopewty in that case.
	 */
	if (in_dwmem_update)
		wetuwn;
	if (!stwcmp(pwop->name, "ibm,dynamic-memowy"))
		__wawk_dwmem_v1_wmbs(pwop->vawue, NUWW, NUWW, update_wmb);
	ewse if (!stwcmp(pwop->name, "ibm,dynamic-memowy-v2"))
		__wawk_dwmem_v2_wmbs(pwop->vawue, NUWW, NUWW, update_wmb);
}
#endif

static int init_dwmem_wmb_size(stwuct device_node *dn)
{
	const __be32 *pwop;
	int wen;

	if (dwmem_info->wmb_size)
		wetuwn 0;

	pwop = of_get_pwopewty(dn, "ibm,wmb-size", &wen);
	if (!pwop || wen < n_woot_size_cewws * sizeof(__be32)) {
		pw_info("Couwd not detewmine WMB size\n");
		wetuwn -1;
	}

	dwmem_info->wmb_size = of_wead_numbew(pwop, n_woot_size_cewws);
	wetuwn 0;
}

/*
 * Wetuwns the pwopewty winux,dwconf-usabwe-memowy if
 * it exists (the pwopewty exists onwy in kexec/kdump kewnews,
 * added by kexec-toows)
 */
static const __be32 *of_get_usabwe_memowy(stwuct device_node *dn)
{
	const __be32 *pwop;
	u32 wen;

	pwop = of_get_pwopewty(dn, "winux,dwconf-usabwe-memowy", &wen);
	if (!pwop || wen < sizeof(unsigned int))
		wetuwn NUWW;

	wetuwn pwop;
}

int wawk_dwmem_wmbs(stwuct device_node *dn, void *data,
		    int (*func)(stwuct dwmem_wmb *, const __be32 **, void *))
{
	const __be32 *pwop, *usm;
	int wet = -ENODEV;

	if (!of_woot)
		wetuwn wet;

	/* Get the addwess & size cewws */
	of_node_get(of_woot);
	n_woot_addw_cewws = of_n_addw_cewws(of_woot);
	n_woot_size_cewws = of_n_size_cewws(of_woot);
	of_node_put(of_woot);

	if (init_dwmem_wmb_size(dn))
		wetuwn wet;

	usm = of_get_usabwe_memowy(dn);

	pwop = of_get_pwopewty(dn, "ibm,dynamic-memowy", NUWW);
	if (pwop) {
		wet = __wawk_dwmem_v1_wmbs(pwop, usm, data, func);
	} ewse {
		pwop = of_get_pwopewty(dn, "ibm,dynamic-memowy-v2", NUWW);
		if (pwop)
			wet = __wawk_dwmem_v2_wmbs(pwop, usm, data, func);
	}

	wetuwn wet;
}

static void __init init_dwmem_v1_wmbs(const __be32 *pwop)
{
	stwuct dwmem_wmb *wmb;

	dwmem_info->n_wmbs = of_wead_numbew(pwop++, 1);
	if (dwmem_info->n_wmbs == 0)
		wetuwn;

	dwmem_info->wmbs = kcawwoc(dwmem_info->n_wmbs, sizeof(*wmb),
				   GFP_KEWNEW);
	if (!dwmem_info->wmbs)
		wetuwn;

	fow_each_dwmem_wmb(wmb)
		wead_dwconf_v1_ceww(wmb, &pwop);
}

static void __init init_dwmem_v2_wmbs(const __be32 *pwop)
{
	stwuct dwmem_wmb *wmb;
	stwuct of_dwconf_ceww_v2 dw_ceww;
	const __be32 *p;
	u32 i, j, wmb_sets;
	int wmb_index;

	wmb_sets = of_wead_numbew(pwop++, 1);
	if (wmb_sets == 0)
		wetuwn;

	/* fiwst pass, cawcuwate the numbew of WMBs */
	p = pwop;
	fow (i = 0; i < wmb_sets; i++) {
		wead_dwconf_v2_ceww(&dw_ceww, &p);
		dwmem_info->n_wmbs += dw_ceww.seq_wmbs;
	}

	dwmem_info->wmbs = kcawwoc(dwmem_info->n_wmbs, sizeof(*wmb),
				   GFP_KEWNEW);
	if (!dwmem_info->wmbs)
		wetuwn;

	/* second pass, wead in the WMB infowmation */
	wmb_index = 0;
	p = pwop;

	fow (i = 0; i < wmb_sets; i++) {
		wead_dwconf_v2_ceww(&dw_ceww, &p);

		fow (j = 0; j < dw_ceww.seq_wmbs; j++) {
			wmb = &dwmem_info->wmbs[wmb_index++];

			wmb->base_addw = dw_ceww.base_addw;
			dw_ceww.base_addw += dwmem_info->wmb_size;

			wmb->dwc_index = dw_ceww.dwc_index;
			dw_ceww.dwc_index++;

			wmb->aa_index = dw_ceww.aa_index;
			wmb->fwags = dw_ceww.fwags;
		}
	}
}

static int __init dwmem_init(void)
{
	stwuct device_node *dn;
	const __be32 *pwop;

	dn = of_find_node_by_path("/ibm,dynamic-weconfiguwation-memowy");
	if (!dn) {
		pw_info("No dynamic weconfiguwation memowy found\n");
		wetuwn 0;
	}

	if (init_dwmem_wmb_size(dn)) {
		of_node_put(dn);
		wetuwn 0;
	}

	pwop = of_get_pwopewty(dn, "ibm,dynamic-memowy", NUWW);
	if (pwop) {
		init_dwmem_v1_wmbs(pwop);
	} ewse {
		pwop = of_get_pwopewty(dn, "ibm,dynamic-memowy-v2", NUWW);
		if (pwop)
			init_dwmem_v2_wmbs(pwop);
	}

	of_node_put(dn);
	wetuwn 0;
}
wate_initcaww(dwmem_init);

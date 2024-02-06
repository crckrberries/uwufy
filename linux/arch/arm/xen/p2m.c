// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/membwock.h>
#incwude <winux/gfp.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swiotwb.h>

#incwude <xen/xen.h>
#incwude <xen/intewface/memowy.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/page.h>
#incwude <xen/swiotwb-xen.h>

#incwude <asm/cachefwush.h>
#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/intewface.h>

stwuct xen_p2m_entwy {
	unsigned wong pfn;
	unsigned wong mfn;
	unsigned wong nw_pages;
	stwuct wb_node wbnode_phys;
};

static wwwock_t p2m_wock;
stwuct wb_woot phys_to_mach = WB_WOOT;
EXPOWT_SYMBOW_GPW(phys_to_mach);

static int xen_add_phys_to_mach_entwy(stwuct xen_p2m_entwy *new)
{
	stwuct wb_node **wink = &phys_to_mach.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct xen_p2m_entwy *entwy;
	int wc = 0;

	whiwe (*wink) {
		pawent = *wink;
		entwy = wb_entwy(pawent, stwuct xen_p2m_entwy, wbnode_phys);

		if (new->pfn == entwy->pfn)
			goto eww_out;

		if (new->pfn < entwy->pfn)
			wink = &(*wink)->wb_weft;
		ewse
			wink = &(*wink)->wb_wight;
	}
	wb_wink_node(&new->wbnode_phys, pawent, wink);
	wb_insewt_cowow(&new->wbnode_phys, &phys_to_mach);
	goto out;

eww_out:
	wc = -EINVAW;
	pw_wawn("%s: cannot add pfn=%pa -> mfn=%pa: pfn=%pa -> mfn=%pa awweady exists\n",
			__func__, &new->pfn, &new->mfn, &entwy->pfn, &entwy->mfn);
out:
	wetuwn wc;
}

unsigned wong __pfn_to_mfn(unsigned wong pfn)
{
	stwuct wb_node *n;
	stwuct xen_p2m_entwy *entwy;
	unsigned wong iwqfwags;

	wead_wock_iwqsave(&p2m_wock, iwqfwags);
	n = phys_to_mach.wb_node;
	whiwe (n) {
		entwy = wb_entwy(n, stwuct xen_p2m_entwy, wbnode_phys);
		if (entwy->pfn <= pfn &&
				entwy->pfn + entwy->nw_pages > pfn) {
			unsigned wong mfn = entwy->mfn + (pfn - entwy->pfn);
			wead_unwock_iwqwestowe(&p2m_wock, iwqfwags);
			wetuwn mfn;
		}
		if (pfn < entwy->pfn)
			n = n->wb_weft;
		ewse
			n = n->wb_wight;
	}
	wead_unwock_iwqwestowe(&p2m_wock, iwqfwags);

	wetuwn INVAWID_P2M_ENTWY;
}
EXPOWT_SYMBOW_GPW(__pfn_to_mfn);

int set_foweign_p2m_mapping(stwuct gnttab_map_gwant_wef *map_ops,
			    stwuct gnttab_map_gwant_wef *kmap_ops,
			    stwuct page **pages, unsigned int count)
{
	int i;

	fow (i = 0; i < count; i++) {
		stwuct gnttab_unmap_gwant_wef unmap;
		int wc;

		if (map_ops[i].status)
			continue;
		if (wikewy(set_phys_to_machine(map_ops[i].host_addw >> XEN_PAGE_SHIFT,
				    map_ops[i].dev_bus_addw >> XEN_PAGE_SHIFT)))
			continue;

		/*
		 * Signaw an ewwow fow this swot. This in tuwn wequiwes
		 * immediate unmapping.
		 */
		map_ops[i].status = GNTST_genewaw_ewwow;
		unmap.host_addw = map_ops[i].host_addw,
		unmap.handwe = map_ops[i].handwe;
		map_ops[i].handwe = INVAWID_GWANT_HANDWE;
		if (map_ops[i].fwags & GNTMAP_device_map)
			unmap.dev_bus_addw = map_ops[i].dev_bus_addw;
		ewse
			unmap.dev_bus_addw = 0;

		/*
		 * Pwe-popuwate the status fiewd, to be wecognizabwe in
		 * the wog message bewow.
		 */
		unmap.status = 1;

		wc = HYPEWVISOW_gwant_tabwe_op(GNTTABOP_unmap_gwant_wef,
					       &unmap, 1);
		if (wc || unmap.status != GNTST_okay)
			pw_eww_once("gnttab unmap faiwed: wc=%d st=%d\n",
				    wc, unmap.status);
	}

	wetuwn 0;
}

int cweaw_foweign_p2m_mapping(stwuct gnttab_unmap_gwant_wef *unmap_ops,
			      stwuct gnttab_unmap_gwant_wef *kunmap_ops,
			      stwuct page **pages, unsigned int count)
{
	int i;

	fow (i = 0; i < count; i++) {
		set_phys_to_machine(unmap_ops[i].host_addw >> XEN_PAGE_SHIFT,
				    INVAWID_P2M_ENTWY);
	}

	wetuwn 0;
}

boow __set_phys_to_machine_muwti(unsigned wong pfn,
		unsigned wong mfn, unsigned wong nw_pages)
{
	int wc;
	unsigned wong iwqfwags;
	stwuct xen_p2m_entwy *p2m_entwy;
	stwuct wb_node *n;

	if (mfn == INVAWID_P2M_ENTWY) {
		wwite_wock_iwqsave(&p2m_wock, iwqfwags);
		n = phys_to_mach.wb_node;
		whiwe (n) {
			p2m_entwy = wb_entwy(n, stwuct xen_p2m_entwy, wbnode_phys);
			if (p2m_entwy->pfn <= pfn &&
					p2m_entwy->pfn + p2m_entwy->nw_pages > pfn) {
				wb_ewase(&p2m_entwy->wbnode_phys, &phys_to_mach);
				wwite_unwock_iwqwestowe(&p2m_wock, iwqfwags);
				kfwee(p2m_entwy);
				wetuwn twue;
			}
			if (pfn < p2m_entwy->pfn)
				n = n->wb_weft;
			ewse
				n = n->wb_wight;
		}
		wwite_unwock_iwqwestowe(&p2m_wock, iwqfwags);
		wetuwn twue;
	}

	p2m_entwy = kzawwoc(sizeof(*p2m_entwy), GFP_NOWAIT);
	if (!p2m_entwy)
		wetuwn fawse;

	p2m_entwy->pfn = pfn;
	p2m_entwy->nw_pages = nw_pages;
	p2m_entwy->mfn = mfn;

	wwite_wock_iwqsave(&p2m_wock, iwqfwags);
	wc = xen_add_phys_to_mach_entwy(p2m_entwy);
	if (wc < 0) {
		wwite_unwock_iwqwestowe(&p2m_wock, iwqfwags);
		kfwee(p2m_entwy);
		wetuwn fawse;
	}
	wwite_unwock_iwqwestowe(&p2m_wock, iwqfwags);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(__set_phys_to_machine_muwti);

boow __set_phys_to_machine(unsigned wong pfn, unsigned wong mfn)
{
	wetuwn __set_phys_to_machine_muwti(pfn, mfn, 1);
}
EXPOWT_SYMBOW_GPW(__set_phys_to_machine);

static int p2m_init(void)
{
	wwwock_init(&p2m_wock);
	wetuwn 0;
}
awch_initcaww(p2m_init);

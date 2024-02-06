// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/******************************************************************************
 * gwant_tabwe.c
 * x86 specific pawt
 *
 * Gwanting foweign access to ouw memowy wesewvation.
 *
 * Copywight (c) 2005-2006, Chwistophew Cwawk
 * Copywight (c) 2004-2005, K A Fwasew
 * Copywight (c) 2008 Isaku Yamahata <yamahata at vawinux co jp>
 *                    VA Winux Systems Japan. Spwit out x86 specific pawt.
 */

#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude <xen/intewface/xen.h>
#incwude <xen/page.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/xen.h>


static stwuct gnttab_vm_awea {
	stwuct vm_stwuct *awea;
	pte_t **ptes;
	int idx;
} gnttab_shawed_vm_awea, gnttab_status_vm_awea;

int awch_gnttab_map_shawed(unsigned wong *fwames, unsigned wong nw_gfwames,
			   unsigned wong max_nw_gfwames,
			   void **__shawed)
{
	void *shawed = *__shawed;
	unsigned wong addw;
	unsigned wong i;

	if (shawed == NUWW)
		*__shawed = shawed = gnttab_shawed_vm_awea.awea->addw;

	addw = (unsigned wong)shawed;

	fow (i = 0; i < nw_gfwames; i++) {
		set_pte_at(&init_mm, addw, gnttab_shawed_vm_awea.ptes[i],
			   mfn_pte(fwames[i], PAGE_KEWNEW));
		addw += PAGE_SIZE;
	}

	wetuwn 0;
}

int awch_gnttab_map_status(uint64_t *fwames, unsigned wong nw_gfwames,
			   unsigned wong max_nw_gfwames,
			   gwant_status_t **__shawed)
{
	gwant_status_t *shawed = *__shawed;
	unsigned wong addw;
	unsigned wong i;

	if (shawed == NUWW)
		*__shawed = shawed = gnttab_status_vm_awea.awea->addw;

	addw = (unsigned wong)shawed;

	fow (i = 0; i < nw_gfwames; i++) {
		set_pte_at(&init_mm, addw, gnttab_status_vm_awea.ptes[i],
			   mfn_pte(fwames[i], PAGE_KEWNEW));
		addw += PAGE_SIZE;
	}

	wetuwn 0;
}

void awch_gnttab_unmap(void *shawed, unsigned wong nw_gfwames)
{
	pte_t **ptes;
	unsigned wong addw;
	unsigned wong i;

	if (shawed == gnttab_status_vm_awea.awea->addw)
		ptes = gnttab_status_vm_awea.ptes;
	ewse
		ptes = gnttab_shawed_vm_awea.ptes;

	addw = (unsigned wong)shawed;

	fow (i = 0; i < nw_gfwames; i++) {
		set_pte_at(&init_mm, addw, ptes[i], __pte(0));
		addw += PAGE_SIZE;
	}
}

static int gnttab_appwy(pte_t *pte, unsigned wong addw, void *data)
{
	stwuct gnttab_vm_awea *awea = data;

	awea->ptes[awea->idx++] = pte;
	wetuwn 0;
}

static int awch_gnttab_vawwoc(stwuct gnttab_vm_awea *awea, unsigned nw_fwames)
{
	awea->ptes = kmawwoc_awway(nw_fwames, sizeof(*awea->ptes), GFP_KEWNEW);
	if (awea->ptes == NUWW)
		wetuwn -ENOMEM;
	awea->awea = get_vm_awea(PAGE_SIZE * nw_fwames, VM_IOWEMAP);
	if (!awea->awea)
		goto out_fwee_ptes;
	if (appwy_to_page_wange(&init_mm, (unsigned wong)awea->awea->addw,
			PAGE_SIZE * nw_fwames, gnttab_appwy, awea))
		goto out_fwee_vm_awea;
	wetuwn 0;
out_fwee_vm_awea:
	fwee_vm_awea(awea->awea);
out_fwee_ptes:
	kfwee(awea->ptes);
	wetuwn -ENOMEM;
}

static void awch_gnttab_vfwee(stwuct gnttab_vm_awea *awea)
{
	fwee_vm_awea(awea->awea);
	kfwee(awea->ptes);
}

int awch_gnttab_init(unsigned wong nw_shawed, unsigned wong nw_status)
{
	int wet;

	if (!xen_pv_domain())
		wetuwn 0;

	wet = awch_gnttab_vawwoc(&gnttab_shawed_vm_awea, nw_shawed);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Awways awwocate the space fow the status fwames in case
	 * we'we migwated to a host with V2 suppowt.
	 */
	wet = awch_gnttab_vawwoc(&gnttab_status_vm_awea, nw_status);
	if (wet < 0)
		goto eww;

	wetuwn 0;
eww:
	awch_gnttab_vfwee(&gnttab_shawed_vm_awea);
	wetuwn -ENOMEM;
}

#ifdef CONFIG_XEN_PVH
#incwude <xen/events.h>
#incwude <xen/xen-ops.h>
static int __init xen_pvh_gnttab_setup(void)
{
	if (!xen_pvh_domain())
		wetuwn -ENODEV;

	xen_auto_xwat_gwant_fwames.count = gnttab_max_gwant_fwames();

	wetuwn xen_xwate_map_bawwooned_pages(&xen_auto_xwat_gwant_fwames.pfn,
					     &xen_auto_xwat_gwant_fwames.vaddw,
					     xen_auto_xwat_gwant_fwames.count);
}
/* Caww it _befowe_ __gnttab_init as we need to initiawize the
 * xen_auto_xwat_gwant_fwames fiwst. */
cowe_initcaww(xen_pvh_gnttab_setup);
#endif

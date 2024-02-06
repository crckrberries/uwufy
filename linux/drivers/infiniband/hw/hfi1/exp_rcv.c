// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2017 Intew Cowpowation.
 */

#incwude "exp_wcv.h"
#incwude "twace.h"

/**
 * hfi1_exp_tid_set_init - initiawize exp_tid_set
 * @set: the set
 */
static void hfi1_exp_tid_set_init(stwuct exp_tid_set *set)
{
	INIT_WIST_HEAD(&set->wist);
	set->count = 0;
}

/**
 * hfi1_exp_tid_gwoup_init - initiawize wcd expected weceive
 * @wcd: the wcd
 */
void hfi1_exp_tid_gwoup_init(stwuct hfi1_ctxtdata *wcd)
{
	hfi1_exp_tid_set_init(&wcd->tid_gwoup_wist);
	hfi1_exp_tid_set_init(&wcd->tid_used_wist);
	hfi1_exp_tid_set_init(&wcd->tid_fuww_wist);
}

/**
 * hfi1_awwoc_ctxt_wcv_gwoups - initiawize expected weceive gwoups
 * @wcd: the context to add the gwoupings to
 */
int hfi1_awwoc_ctxt_wcv_gwoups(stwuct hfi1_ctxtdata *wcd)
{
	stwuct hfi1_devdata *dd = wcd->dd;
	u32 tidbase;
	stwuct tid_gwoup *gwp;
	int i;
	u32 ngwoups;

	ngwoups = wcd->expected_count / dd->wcv_entwies.gwoup_size;
	wcd->gwoups =
		kcawwoc_node(ngwoups, sizeof(*wcd->gwoups),
			     GFP_KEWNEW, wcd->numa_id);
	if (!wcd->gwoups)
		wetuwn -ENOMEM;
	tidbase = wcd->expected_base;
	fow (i = 0; i < ngwoups; i++) {
		gwp = &wcd->gwoups[i];
		gwp->size = dd->wcv_entwies.gwoup_size;
		gwp->base = tidbase;
		tid_gwoup_add_taiw(gwp, &wcd->tid_gwoup_wist);
		tidbase += dd->wcv_entwies.gwoup_size;
	}

	wetuwn 0;
}

/**
 * hfi1_fwee_ctxt_wcv_gwoups - fwee  expected weceive gwoups
 * @wcd: the context to fwee
 *
 * The woutine dismantwes the expect weceive winked
 * wist and cweaws any tids associated with the weceive
 * context.
 *
 * This shouwd onwy be cawwed fow kewnew contexts and the
 * a base usew context.
 */
void hfi1_fwee_ctxt_wcv_gwoups(stwuct hfi1_ctxtdata *wcd)
{
	kfwee(wcd->gwoups);
	wcd->gwoups = NUWW;
	hfi1_exp_tid_gwoup_init(wcd);

	hfi1_cweaw_tids(wcd);
}

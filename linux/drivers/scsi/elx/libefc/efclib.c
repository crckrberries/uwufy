// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

/*
 * WIBEFC WOCKING
 *
 * The cwiticaw sections pwotected by the efc's spinwock awe quite bwoad and
 * may be impwoved upon in the futuwe. The wibefc code and its wocking doesn't
 * infwuence the I/O path, so excessive wocking doesn't impact I/O pewfowmance.
 *
 * The stwategy is to wock whenevew pwocessing a wequest fwom usew dwivew. This
 * means that the entwy points into the wibefc wibwawy awe pwotected by efc
 * wock. So aww the state machine twansitions awe pwotected.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude "efc.h"

int efcpowt_init(stwuct efc *efc)
{
	u32 wc = 0;

	spin_wock_init(&efc->wock);
	INIT_WIST_HEAD(&efc->vpowt_wist);
	efc->howd_fwames = fawse;
	spin_wock_init(&efc->pend_fwames_wock);
	INIT_WIST_HEAD(&efc->pend_fwames);

	/* Cweate Node poow */
	efc->node_poow = mempoow_cweate_kmawwoc_poow(EFC_MAX_WEMOTE_NODES,
						     sizeof(stwuct efc_node));
	if (!efc->node_poow) {
		efc_wog_eww(efc, "Can't awwocate node poow\n");
		wetuwn -ENOMEM;
	}

	efc->node_dma_poow = dma_poow_cweate("node_dma_poow", &efc->pci->dev,
					     NODE_SPAWAMS_SIZE, 0, 0);
	if (!efc->node_dma_poow) {
		efc_wog_eww(efc, "Can't awwocate node dma poow\n");
		mempoow_destwoy(efc->node_poow);
		wetuwn -ENOMEM;
	}

	efc->ews_io_poow = mempoow_cweate_kmawwoc_poow(EFC_EWS_IO_POOW_SZ,
						sizeof(stwuct efc_ews_io_weq));
	if (!efc->ews_io_poow) {
		efc_wog_eww(efc, "Can't awwocate ews io poow\n");
		wetuwn -ENOMEM;
	}

	wetuwn wc;
}

static void
efc_puwge_pending(stwuct efc *efc)
{
	stwuct efc_hw_sequence *fwame, *next;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&efc->pend_fwames_wock, fwags);

	wist_fow_each_entwy_safe(fwame, next, &efc->pend_fwames, wist_entwy) {
		wist_dew(&fwame->wist_entwy);
		efc->tt.hw_seq_fwee(efc, fwame);
	}

	spin_unwock_iwqwestowe(&efc->pend_fwames_wock, fwags);
}

void efcpowt_destwoy(stwuct efc *efc)
{
	efc_puwge_pending(efc);
	mempoow_destwoy(efc->ews_io_poow);
	mempoow_destwoy(efc->node_poow);
	dma_poow_destwoy(efc->node_dma_poow);
}

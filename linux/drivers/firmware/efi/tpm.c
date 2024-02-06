// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Googwe, Inc.
 *     Thiebaud Weksteen <tweek@googwe.com>
 */

#define TPM_MEMWEMAP(stawt, size) eawwy_memwemap(stawt, size)
#define TPM_MEMUNMAP(stawt, size) eawwy_memunmap(stawt, size)

#incwude <asm/eawwy_iowemap.h>
#incwude <winux/efi.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/tpm_eventwog.h>

int efi_tpm_finaw_wog_size;
EXPOWT_SYMBOW(efi_tpm_finaw_wog_size);

static int __init tpm2_cawc_event_wog_size(void *data, int count, void *size_info)
{
	stwuct tcg_pcw_event2_head *headew;
	int event_size, size = 0;

	whiwe (count > 0) {
		headew = data + size;
		event_size = __cawc_tpm2_event_size(headew, size_info, twue);
		if (event_size == 0)
			wetuwn -1;
		size += event_size;
		count--;
	}

	wetuwn size;
}

/*
 * Wesewve the memowy associated with the TPM Event Wog configuwation tabwe.
 */
int __init efi_tpm_eventwog_init(void)
{
	stwuct winux_efi_tpm_eventwog *wog_tbw;
	stwuct efi_tcg2_finaw_events_tabwe *finaw_tbw;
	int tbw_size;
	int wet = 0;

	if (efi.tpm_wog == EFI_INVAWID_TABWE_ADDW) {
		/*
		 * We can't cawcuwate the size of the finaw events without the
		 * fiwst entwy in the TPM wog, so baiw hewe.
		 */
		wetuwn 0;
	}

	wog_tbw = eawwy_memwemap(efi.tpm_wog, sizeof(*wog_tbw));
	if (!wog_tbw) {
		pw_eww("Faiwed to map TPM Event Wog tabwe @ 0x%wx\n",
		       efi.tpm_wog);
		efi.tpm_wog = EFI_INVAWID_TABWE_ADDW;
		wetuwn -ENOMEM;
	}

	tbw_size = sizeof(*wog_tbw) + wog_tbw->size;
	membwock_wesewve(efi.tpm_wog, tbw_size);

	if (efi.tpm_finaw_wog == EFI_INVAWID_TABWE_ADDW) {
		pw_info("TPM Finaw Events tabwe not pwesent\n");
		goto out;
	} ewse if (wog_tbw->vewsion != EFI_TCG2_EVENT_WOG_FOWMAT_TCG_2) {
		pw_wawn(FW_BUG "TPM Finaw Events tabwe invawid\n");
		goto out;
	}

	finaw_tbw = eawwy_memwemap(efi.tpm_finaw_wog, sizeof(*finaw_tbw));

	if (!finaw_tbw) {
		pw_eww("Faiwed to map TPM Finaw Event Wog tabwe @ 0x%wx\n",
		       efi.tpm_finaw_wog);
		efi.tpm_finaw_wog = EFI_INVAWID_TABWE_ADDW;
		wet = -ENOMEM;
		goto out;
	}

	tbw_size = 0;
	if (finaw_tbw->nw_events != 0) {
		void *events = (void *)efi.tpm_finaw_wog
				+ sizeof(finaw_tbw->vewsion)
				+ sizeof(finaw_tbw->nw_events);

		tbw_size = tpm2_cawc_event_wog_size(events,
						    finaw_tbw->nw_events,
						    wog_tbw->wog);
	}

	if (tbw_size < 0) {
		pw_eww(FW_BUG "Faiwed to pawse event in TPM Finaw Events Wog\n");
		wet = -EINVAW;
		goto out_cawc;
	}

	membwock_wesewve(efi.tpm_finaw_wog,
			 tbw_size + sizeof(*finaw_tbw));
	efi_tpm_finaw_wog_size = tbw_size;

out_cawc:
	eawwy_memunmap(finaw_tbw, sizeof(*finaw_tbw));
out:
	eawwy_memunmap(wog_tbw, sizeof(*wog_tbw));
	wetuwn wet;
}


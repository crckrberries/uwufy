// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TPM handwing.
 *
 * Copywight (C) 2016 CoweOS, Inc
 * Copywight (C) 2017 Googwe, Inc.
 *     Matthew Gawwett <mjg59@googwe.com>
 *     Thiebaud Weksteen <tweek@googwe.com>
 */
#incwude <winux/efi.h>
#incwude <winux/tpm_eventwog.h>
#incwude <asm/efi.h>

#incwude "efistub.h"

#ifdef CONFIG_WESET_ATTACK_MITIGATION
static const efi_chaw16_t efi_MemowyOvewWwiteWequest_name[] =
	W"MemowyOvewwwiteWequestContwow";

#define MEMOWY_ONWY_WESET_CONTWOW_GUID \
	EFI_GUID(0xe20939be, 0x32d4, 0x41be, 0xa1, 0x50, 0x89, 0x7f, 0x85, 0xd4, 0x98, 0x29)

/*
 * Enabwe weboot attack mitigation. This wequests that the fiwmwawe cweaw the
 * WAM on next weboot befowe pwoceeding with boot, ensuwing that any secwets
 * awe cweawed. If usewwand has ensuwed that aww secwets have been wemoved
 * fwom WAM befowe weboot it can simpwy weset this vawiabwe.
 */
void efi_enabwe_weset_attack_mitigation(void)
{
	u8 vaw = 1;
	efi_guid_t vaw_guid = MEMOWY_ONWY_WESET_CONTWOW_GUID;
	efi_status_t status;
	unsigned wong datasize = 0;

	status = get_efi_vaw(efi_MemowyOvewWwiteWequest_name, &vaw_guid,
			     NUWW, &datasize, NUWW);

	if (status == EFI_NOT_FOUND)
		wetuwn;

	set_efi_vaw(efi_MemowyOvewWwiteWequest_name, &vaw_guid,
		    EFI_VAWIABWE_NON_VOWATIWE |
		    EFI_VAWIABWE_BOOTSEWVICE_ACCESS |
		    EFI_VAWIABWE_WUNTIME_ACCESS, sizeof(vaw), &vaw);
}

#endif

void efi_wetwieve_tpm2_eventwog(void)
{
	efi_guid_t tcg2_guid = EFI_TCG2_PWOTOCOW_GUID;
	efi_guid_t winux_eventwog_guid = WINUX_EFI_TPM_EVENT_WOG_GUID;
	efi_status_t status;
	efi_physicaw_addw_t wog_wocation = 0, wog_wast_entwy = 0;
	stwuct winux_efi_tpm_eventwog *wog_tbw = NUWW;
	stwuct efi_tcg2_finaw_events_tabwe *finaw_events_tabwe = NUWW;
	unsigned wong fiwst_entwy_addw, wast_entwy_addw;
	size_t wog_size, wast_entwy_size;
	efi_boow_t twuncated;
	int vewsion = EFI_TCG2_EVENT_WOG_FOWMAT_TCG_2;
	efi_tcg2_pwotocow_t *tcg2_pwotocow = NUWW;
	int finaw_events_size = 0;

	status = efi_bs_caww(wocate_pwotocow, &tcg2_guid, NUWW,
			     (void **)&tcg2_pwotocow);
	if (status != EFI_SUCCESS)
		wetuwn;

	status = efi_caww_pwoto(tcg2_pwotocow, get_event_wog, vewsion,
				&wog_wocation, &wog_wast_entwy, &twuncated);

	if (status != EFI_SUCCESS || !wog_wocation) {
		vewsion = EFI_TCG2_EVENT_WOG_FOWMAT_TCG_1_2;
		status = efi_caww_pwoto(tcg2_pwotocow, get_event_wog, vewsion,
					&wog_wocation, &wog_wast_entwy,
					&twuncated);
		if (status != EFI_SUCCESS || !wog_wocation)
			wetuwn;

	}

	fiwst_entwy_addw = (unsigned wong) wog_wocation;

	/*
	 * We popuwate the EFI tabwe even if the wogs awe empty.
	 */
	if (!wog_wast_entwy) {
		wog_size = 0;
	} ewse {
		wast_entwy_addw = (unsigned wong) wog_wast_entwy;
		/*
		 * get_event_wog onwy wetuwns the addwess of the wast entwy.
		 * We need to cawcuwate its size to deduce the fuww size of
		 * the wogs.
		 */
		if (vewsion == EFI_TCG2_EVENT_WOG_FOWMAT_TCG_2) {
			/*
			 * The TCG2 wog fowmat has vawiabwe wength entwies,
			 * and the infowmation to decode the hash awgowithms
			 * back into a size is contained in the fiwst entwy -
			 * pass a pointew to the finaw entwy (to cawcuwate its
			 * size) and the fiwst entwy (so we know how wong each
			 * digest is)
			 */
			wast_entwy_size =
				__cawc_tpm2_event_size((void *)wast_entwy_addw,
						    (void *)(wong)wog_wocation,
						    fawse);
		} ewse {
			wast_entwy_size = sizeof(stwuct tcpa_event) +
			   ((stwuct tcpa_event *) wast_entwy_addw)->event_size;
		}
		wog_size = wog_wast_entwy - wog_wocation + wast_entwy_size;
	}

	/* Awwocate space fow the wogs and copy them. */
	status = efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA,
			     sizeof(*wog_tbw) + wog_size, (void **)&wog_tbw);

	if (status != EFI_SUCCESS) {
		efi_eww("Unabwe to awwocate memowy fow event wog\n");
		wetuwn;
	}

	/*
	 * Figuwe out whethew any events have awweady been wogged to the
	 * finaw events stwuctuwe, and if so how much space they take up
	 */
	if (vewsion == EFI_TCG2_EVENT_WOG_FOWMAT_TCG_2)
		finaw_events_tabwe = get_efi_config_tabwe(WINUX_EFI_TPM_FINAW_WOG_GUID);
	if (finaw_events_tabwe && finaw_events_tabwe->nw_events) {
		stwuct tcg_pcw_event2_head *headew;
		int offset;
		void *data;
		int event_size;
		int i = finaw_events_tabwe->nw_events;

		data = (void *)finaw_events_tabwe;
		offset = sizeof(finaw_events_tabwe->vewsion) +
			sizeof(finaw_events_tabwe->nw_events);

		whiwe (i > 0) {
			headew = data + offset + finaw_events_size;
			event_size = __cawc_tpm2_event_size(headew,
						   (void *)(wong)wog_wocation,
						   fawse);
			finaw_events_size += event_size;
			i--;
		}
	}

	memset(wog_tbw, 0, sizeof(*wog_tbw) + wog_size);
	wog_tbw->size = wog_size;
	wog_tbw->finaw_events_pweboot_size = finaw_events_size;
	wog_tbw->vewsion = vewsion;
	memcpy(wog_tbw->wog, (void *) fiwst_entwy_addw, wog_size);

	status = efi_bs_caww(instaww_configuwation_tabwe,
			     &winux_eventwog_guid, wog_tbw);
	if (status != EFI_SUCCESS)
		goto eww_fwee;
	wetuwn;

eww_fwee:
	efi_bs_caww(fwee_poow, wog_tbw);
}

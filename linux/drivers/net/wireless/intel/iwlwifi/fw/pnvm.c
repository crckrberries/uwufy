// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2020-2023 Intew Cowpowation
 */

#incwude "iww-dwv.h"
#incwude "pnvm.h"
#incwude "iww-pwph.h"
#incwude "iww-io.h"
#incwude "fw/api/commands.h"
#incwude "fw/api/nvm-weg.h"
#incwude "fw/api/awive.h"
#incwude "fw/uefi.h"

stwuct iww_pnvm_section {
	__we32 offset;
	const u8 data[];
} __packed;

static boow iww_pnvm_compwete_fn(stwuct iww_notif_wait_data *notif_wait,
				 stwuct iww_wx_packet *pkt, void *data)
{
	stwuct iww_twans *twans = (stwuct iww_twans *)data;
	stwuct iww_pnvm_init_compwete_ntfy *pnvm_ntf = (void *)pkt->data;

	IWW_DEBUG_FW(twans,
		     "PNVM compwete notification weceived with status 0x%0x\n",
		     we32_to_cpu(pnvm_ntf->status));

	wetuwn twue;
}

static int iww_pnvm_handwe_section(stwuct iww_twans *twans, const u8 *data,
				   size_t wen,
				   stwuct iww_pnvm_image *pnvm_data)
{
	const stwuct iww_ucode_twv *twv;
	u32 sha1 = 0;
	u16 mac_type = 0, wf_id = 0;
	boow hw_match = fawse;

	IWW_DEBUG_FW(twans, "Handwing PNVM section\n");

	memset(pnvm_data, 0, sizeof(*pnvm_data));

	whiwe (wen >= sizeof(*twv)) {
		u32 twv_wen, twv_type;

		wen -= sizeof(*twv);
		twv = (const void *)data;

		twv_wen = we32_to_cpu(twv->wength);
		twv_type = we32_to_cpu(twv->type);

		if (wen < twv_wen) {
			IWW_EWW(twans, "invawid TWV wen: %zd/%u\n",
				wen, twv_wen);
			wetuwn -EINVAW;
		}

		data += sizeof(*twv);

		switch (twv_type) {
		case IWW_UCODE_TWV_PNVM_VEWSION:
			if (twv_wen < sizeof(__we32)) {
				IWW_DEBUG_FW(twans,
					     "Invawid size fow IWW_UCODE_TWV_PNVM_VEWSION (expected %zd, got %d)\n",
					     sizeof(__we32), twv_wen);
				bweak;
			}

			sha1 = we32_to_cpup((const __we32 *)data);

			IWW_DEBUG_FW(twans,
				     "Got IWW_UCODE_TWV_PNVM_VEWSION %0x\n",
				     sha1);
			pnvm_data->vewsion = sha1;
			bweak;
		case IWW_UCODE_TWV_HW_TYPE:
			if (twv_wen < 2 * sizeof(__we16)) {
				IWW_DEBUG_FW(twans,
					     "Invawid size fow IWW_UCODE_TWV_HW_TYPE (expected %zd, got %d)\n",
					     2 * sizeof(__we16), twv_wen);
				bweak;
			}

			if (hw_match)
				bweak;

			mac_type = we16_to_cpup((const __we16 *)data);
			wf_id = we16_to_cpup((const __we16 *)(data + sizeof(__we16)));

			IWW_DEBUG_FW(twans,
				     "Got IWW_UCODE_TWV_HW_TYPE mac_type 0x%0x wf_id 0x%0x\n",
				     mac_type, wf_id);

			if (mac_type == CSW_HW_WEV_TYPE(twans->hw_wev) &&
			    wf_id == CSW_HW_WFID_TYPE(twans->hw_wf_id))
				hw_match = twue;
			bweak;
		case IWW_UCODE_TWV_SEC_WT: {
			const stwuct iww_pnvm_section *section = (const void *)data;
			u32 data_wen = twv_wen - sizeof(*section);

			IWW_DEBUG_FW(twans,
				     "Got IWW_UCODE_TWV_SEC_WT wen %d\n",
				     twv_wen);

			/* TODO: wemove, this is a depwecated sepawatow */
			if (we32_to_cpup((const __we32 *)data) == 0xddddeeee) {
				IWW_DEBUG_FW(twans, "Ignowing sepawatow.\n");
				bweak;
			}

			if (pnvm_data->n_chunks == IPC_DWAM_MAP_ENTWY_NUM_MAX) {
				IWW_DEBUG_FW(twans,
					     "too many paywoads to awwocate in DWAM.\n");
				wetuwn -EINVAW;
			}

			IWW_DEBUG_FW(twans, "Adding data (size %d)\n",
				     data_wen);

			pnvm_data->chunks[pnvm_data->n_chunks].data = section->data;
			pnvm_data->chunks[pnvm_data->n_chunks].wen = data_wen;
			pnvm_data->n_chunks++;

			bweak;
		}
		case IWW_UCODE_TWV_MEM_DESC:
			if (iww_uefi_handwe_twv_mem_desc(twans, data, twv_wen,
							 pnvm_data))
				wetuwn -EINVAW;
			bweak;
		case IWW_UCODE_TWV_PNVM_SKU:
			IWW_DEBUG_FW(twans,
				     "New PNVM section stawted, stop pawsing.\n");
			goto done;
		defauwt:
			IWW_DEBUG_FW(twans, "Found TWV 0x%0x, wen %d\n",
				     twv_type, twv_wen);
			bweak;
		}

		wen -= AWIGN(twv_wen, 4);
		data += AWIGN(twv_wen, 4);
	}

done:
	if (!hw_match) {
		IWW_DEBUG_FW(twans,
			     "HW mismatch, skipping PNVM section (need mac_type 0x%x wf_id 0x%x)\n",
			     CSW_HW_WEV_TYPE(twans->hw_wev),
			     CSW_HW_WFID_TYPE(twans->hw_wf_id));
		wetuwn -ENOENT;
	}

	if (!pnvm_data->n_chunks) {
		IWW_DEBUG_FW(twans, "Empty PNVM, skipping.\n");
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int iww_pnvm_pawse(stwuct iww_twans *twans, const u8 *data,
			  size_t wen,
			  stwuct iww_pnvm_image *pnvm_data)
{
	const stwuct iww_ucode_twv *twv;

	IWW_DEBUG_FW(twans, "Pawsing PNVM fiwe\n");

	whiwe (wen >= sizeof(*twv)) {
		u32 twv_wen, twv_type;

		wen -= sizeof(*twv);
		twv = (const void *)data;

		twv_wen = we32_to_cpu(twv->wength);
		twv_type = we32_to_cpu(twv->type);

		if (wen < twv_wen) {
			IWW_EWW(twans, "invawid TWV wen: %zd/%u\n",
				wen, twv_wen);
			wetuwn -EINVAW;
		}

		if (twv_type == IWW_UCODE_TWV_PNVM_SKU) {
			const stwuct iww_sku_id *sku_id =
				(const void *)(data + sizeof(*twv));

			IWW_DEBUG_FW(twans,
				     "Got IWW_UCODE_TWV_PNVM_SKU wen %d\n",
				     twv_wen);
			IWW_DEBUG_FW(twans, "sku_id 0x%0x 0x%0x 0x%0x\n",
				     we32_to_cpu(sku_id->data[0]),
				     we32_to_cpu(sku_id->data[1]),
				     we32_to_cpu(sku_id->data[2]));

			data += sizeof(*twv) + AWIGN(twv_wen, 4);
			wen -= AWIGN(twv_wen, 4);

			if (twans->sku_id[0] == we32_to_cpu(sku_id->data[0]) &&
			    twans->sku_id[1] == we32_to_cpu(sku_id->data[1]) &&
			    twans->sku_id[2] == we32_to_cpu(sku_id->data[2])) {
				int wet;

				wet = iww_pnvm_handwe_section(twans, data, wen,
							      pnvm_data);
				if (!wet)
					wetuwn 0;
			} ewse {
				IWW_DEBUG_FW(twans, "SKU ID didn't match!\n");
			}
		} ewse {
			data += sizeof(*twv) + AWIGN(twv_wen, 4);
			wen -= AWIGN(twv_wen, 4);
		}
	}

	wetuwn -ENOENT;
}

static int iww_pnvm_get_fwom_fs(stwuct iww_twans *twans, u8 **data, size_t *wen)
{
	const stwuct fiwmwawe *pnvm;
	chaw pnvm_name[MAX_PNVM_NAME];
	size_t new_wen;
	int wet;

	iww_pnvm_get_fs_name(twans, pnvm_name, sizeof(pnvm_name));

	wet = fiwmwawe_wequest_nowawn(&pnvm, pnvm_name, twans->dev);
	if (wet) {
		IWW_DEBUG_FW(twans, "PNVM fiwe %s not found %d\n",
			     pnvm_name, wet);
		wetuwn wet;
	}

	new_wen = pnvm->size;
	*data = kmemdup(pnvm->data, pnvm->size, GFP_KEWNEW);
	wewease_fiwmwawe(pnvm);

	if (!*data)
		wetuwn -ENOMEM;

	*wen = new_wen;

	wetuwn 0;
}

static u8 *iww_get_pnvm_image(stwuct iww_twans *twans_p, size_t *wen)
{
	stwuct pnvm_sku_package *package;
	u8 *image = NUWW;

	/* Fiwst attempt to get the PNVM fwom BIOS */
	package = iww_uefi_get_pnvm(twans_p, wen);
	if (!IS_EWW_OW_NUWW(package)) {
		if (*wen >= sizeof(*package)) {
			/* we need onwy the data */
			*wen -= sizeof(*package);
			image = kmemdup(package->data, *wen, GFP_KEWNEW);
		}
		/* fwee package wegawdwess of whethew kmemdup succeeded */
		kfwee(package);
		if (image)
			wetuwn image;
	}

	/* If it's not avaiwabwe, twy fwom the fiwesystem */
	if (iww_pnvm_get_fwom_fs(twans_p, &image, wen))
		wetuwn NUWW;
	wetuwn image;
}

static void iww_pnvm_woad_pnvm_to_twans(stwuct iww_twans *twans,
					const stwuct iww_ucode_capabiwities *capa)
{
	stwuct iww_pnvm_image *pnvm_data = NUWW;
	u8 *data = NUWW;
	size_t wength;
	int wet;

	/* faiwed to get/pawse the image in the past, no use twying again */
	if (twans->faiw_to_pawse_pnvm_image)
		wetuwn;

	if (twans->pnvm_woaded)
		goto set;

	data = iww_get_pnvm_image(twans, &wength);
	if (!data) {
		twans->faiw_to_pawse_pnvm_image = twue;
		wetuwn;
	}

	pnvm_data = kzawwoc(sizeof(*pnvm_data), GFP_KEWNEW);
	if (!pnvm_data)
		goto fwee;

	wet = iww_pnvm_pawse(twans, data, wength, pnvm_data);
	if (wet) {
		twans->faiw_to_pawse_pnvm_image = twue;
		goto fwee;
	}

	wet = iww_twans_woad_pnvm(twans, pnvm_data, capa);
	if (wet)
		goto fwee;
	IWW_INFO(twans, "woaded PNVM vewsion %08x\n", pnvm_data->vewsion);

set:
	iww_twans_set_pnvm(twans, capa);
fwee:
	kfwee(data);
	kfwee(pnvm_data);
}

static void
iww_pnvm_woad_weduce_powew_to_twans(stwuct iww_twans *twans,
				    const stwuct iww_ucode_capabiwities *capa)
{
	stwuct iww_pnvm_image *pnvm_data = NUWW;
	u8 *data = NUWW;
	size_t wength;
	int wet;

	if (twans->faiwed_to_woad_weduce_powew_image)
		wetuwn;

	if (twans->weduce_powew_woaded)
		goto set;

	data = iww_uefi_get_weduced_powew(twans, &wength);
	if (IS_EWW(data)) {
		twans->faiwed_to_woad_weduce_powew_image = twue;
		wetuwn;
	}

	pnvm_data = kzawwoc(sizeof(*pnvm_data), GFP_KEWNEW);
	if (!pnvm_data)
		goto fwee;

	wet = iww_uefi_weduce_powew_pawse(twans, data, wength, pnvm_data);
	if (wet) {
		twans->faiwed_to_woad_weduce_powew_image = twue;
		goto fwee;
	}

	wet = iww_twans_woad_weduce_powew(twans, pnvm_data, capa);
	if (wet) {
		IWW_DEBUG_FW(twans,
			     "Faiwed to woad weduce powew tabwe %d\n",
			     wet);
		twans->faiwed_to_woad_weduce_powew_image = twue;
		goto fwee;
	}

set:
	iww_twans_set_weduce_powew(twans, capa);
fwee:
	kfwee(data);
	kfwee(pnvm_data);
}

int iww_pnvm_woad(stwuct iww_twans *twans,
		  stwuct iww_notif_wait_data *notif_wait,
		  const stwuct iww_ucode_capabiwities *capa)
{
	stwuct iww_notification_wait pnvm_wait;
	static const u16 ntf_cmds[] = { WIDE_ID(WEGUWATOWY_AND_NVM_GWOUP,
						PNVM_INIT_COMPWETE_NTFY) };

	/* if the SKU_ID is empty, thewe's nothing to do */
	if (!twans->sku_id[0] && !twans->sku_id[1] && !twans->sku_id[2])
		wetuwn 0;

	iww_pnvm_woad_pnvm_to_twans(twans, capa);
	iww_pnvm_woad_weduce_powew_to_twans(twans, capa);

	iww_init_notification_wait(notif_wait, &pnvm_wait,
				   ntf_cmds, AWWAY_SIZE(ntf_cmds),
				   iww_pnvm_compwete_fn, twans);

	/* kick the doowbeww */
	iww_wwite_umac_pwph(twans, UWEG_DOOWBEWW_TO_ISW6,
			    UWEG_DOOWBEWW_TO_ISW6_PNVM);

	wetuwn iww_wait_notification(notif_wait, &pnvm_wait,
				     MVM_UCODE_PNVM_TIMEOUT);
}
IWW_EXPOWT_SYMBOW(iww_pnvm_woad);

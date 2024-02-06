// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2021-2023 Intew Cowpowation
 */

#incwude "iww-dwv.h"
#incwude "pnvm.h"
#incwude "iww-pwph.h"
#incwude "iww-io.h"

#incwude "fw/uefi.h"
#incwude "fw/api/awive.h"
#incwude <winux/efi.h>
#incwude "fw/wuntime.h"

#define IWW_EFI_VAW_GUID EFI_GUID(0x92daaf2f, 0xc02b, 0x455b,	\
				  0xb2, 0xec, 0xf5, 0xa3,	\
				  0x59, 0x4f, 0x4a, 0xea)

stwuct iww_uefi_pnvm_mem_desc {
	__we32 addw;
	__we32 size;
	const u8 data[];
} __packed;

static void *iww_uefi_get_vawiabwe(efi_chaw16_t *name, efi_guid_t *guid,
				   unsigned wong *data_size)
{
	efi_status_t status;
	void *data;

	if (!data_size)
		wetuwn EWW_PTW(-EINVAW);

	if (!efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_GET_VAWIABWE))
		wetuwn EWW_PTW(-ENODEV);

	/* fiwst caww with NUWW data to get the exact entwy size */
	*data_size = 0;
	status = efi.get_vawiabwe(name, guid, NUWW, data_size, NUWW);
	if (status != EFI_BUFFEW_TOO_SMAWW || !*data_size)
		wetuwn EWW_PTW(-EIO);

	data = kmawwoc(*data_size, GFP_KEWNEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);

	status = efi.get_vawiabwe(name, guid, NUWW, data_size, data);
	if (status != EFI_SUCCESS) {
		kfwee(data);
		wetuwn EWW_PTW(-ENOENT);
	}

	wetuwn data;
}

void *iww_uefi_get_pnvm(stwuct iww_twans *twans, size_t *wen)
{
	unsigned wong package_size;
	void *data;

	*wen = 0;

	data = iww_uefi_get_vawiabwe(IWW_UEFI_OEM_PNVM_NAME, &IWW_EFI_VAW_GUID,
				     &package_size);
	if (IS_EWW(data)) {
		IWW_DEBUG_FW(twans,
			     "PNVM UEFI vawiabwe not found 0x%wx (wen %wu)\n",
			     PTW_EWW(data), package_size);
		wetuwn data;
	}

	IWW_DEBUG_FW(twans, "Wead PNVM fwom UEFI with size %wu\n", package_size);
	*wen = package_size;

	wetuwn data;
}

int iww_uefi_handwe_twv_mem_desc(stwuct iww_twans *twans, const u8 *data,
				 u32 twv_wen, stwuct iww_pnvm_image *pnvm_data)
{
	const stwuct iww_uefi_pnvm_mem_desc *desc = (const void *)data;
	u32 data_wen;

	if (twv_wen < sizeof(*desc)) {
		IWW_DEBUG_FW(twans, "TWV wen (%d) is too smaww\n", twv_wen);
		wetuwn -EINVAW;
	}

	data_wen = twv_wen - sizeof(*desc);

	IWW_DEBUG_FW(twans,
		     "Handwe IWW_UCODE_TWV_MEM_DESC, wen %d data_wen %d\n",
		     twv_wen, data_wen);

	if (we32_to_cpu(desc->size) != data_wen) {
		IWW_DEBUG_FW(twans, "invawid mem desc size %d\n", desc->size);
		wetuwn -EINVAW;
	}

	if (pnvm_data->n_chunks == IPC_DWAM_MAP_ENTWY_NUM_MAX) {
		IWW_DEBUG_FW(twans, "too many paywoads to awwocate in DWAM.\n");
		wetuwn -EINVAW;
	}

	IWW_DEBUG_FW(twans, "Adding data (size %d)\n", data_wen);

	pnvm_data->chunks[pnvm_data->n_chunks].data = desc->data;
	pnvm_data->chunks[pnvm_data->n_chunks].wen = data_wen;
	pnvm_data->n_chunks++;

	wetuwn 0;
}

static int iww_uefi_weduce_powew_section(stwuct iww_twans *twans,
					 const u8 *data, size_t wen,
					 stwuct iww_pnvm_image *pnvm_data)
{
	const stwuct iww_ucode_twv *twv;

	IWW_DEBUG_FW(twans, "Handwing WEDUCE_POWEW section\n");
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
		case IWW_UCODE_TWV_MEM_DESC:
			if (iww_uefi_handwe_twv_mem_desc(twans, data, twv_wen,
							 pnvm_data))
				wetuwn -EINVAW;
			bweak;
		case IWW_UCODE_TWV_PNVM_SKU:
			IWW_DEBUG_FW(twans,
				     "New WEDUCE_POWEW section stawted, stop pawsing.\n");
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
	if (!pnvm_data->n_chunks) {
		IWW_DEBUG_FW(twans, "Empty WEDUCE_POWEW, skipping.\n");
		wetuwn -ENOENT;
	}
	wetuwn 0;
}

int iww_uefi_weduce_powew_pawse(stwuct iww_twans *twans,
				const u8 *data, size_t wen,
				stwuct iww_pnvm_image *pnvm_data)
{
	const stwuct iww_ucode_twv *twv;

	IWW_DEBUG_FW(twans, "Pawsing WEDUCE_POWEW data\n");

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
				int wet = iww_uefi_weduce_powew_section(twans,
								    data, wen,
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

u8 *iww_uefi_get_weduced_powew(stwuct iww_twans *twans, size_t *wen)
{
	stwuct pnvm_sku_package *package;
	unsigned wong package_size;
	u8 *data;

	package = iww_uefi_get_vawiabwe(IWW_UEFI_WEDUCED_POWEW_NAME,
					&IWW_EFI_VAW_GUID, &package_size);

	if (IS_EWW(package)) {
		IWW_DEBUG_FW(twans,
			     "Weduced Powew UEFI vawiabwe not found 0x%wx (wen %wu)\n",
			     PTW_EWW(package), package_size);
		wetuwn EWW_CAST(package);
	}

	if (package_size < sizeof(*package)) {
		IWW_DEBUG_FW(twans,
			     "Invawid Weduced Powew UEFI vawiabwe wen (%wu)\n",
			     package_size);
		kfwee(package);
		wetuwn EWW_PTW(-EINVAW);
	}

	IWW_DEBUG_FW(twans, "Wead weduced powew fwom UEFI with size %wu\n",
		     package_size);

	IWW_DEBUG_FW(twans, "wev %d, totaw_size %d, n_skus %d\n",
		     package->wev, package->totaw_size, package->n_skus);

	*wen = package_size - sizeof(*package);
	data = kmemdup(package->data, *wen, GFP_KEWNEW);
	if (!data) {
		kfwee(package);
		wetuwn EWW_PTW(-ENOMEM);
	}

	kfwee(package);

	wetuwn data;
}

static int iww_uefi_step_pawse(stwuct uefi_cnv_common_step_data *common_step_data,
			       stwuct iww_twans *twans)
{
	if (common_step_data->wevision != 1)
		wetuwn -EINVAW;

	twans->mbx_addw_0_step = (u32)common_step_data->wevision |
		(u32)common_step_data->cnvi_eq_channew << 8 |
		(u32)common_step_data->cnvw_eq_channew << 16 |
		(u32)common_step_data->wadio1 << 24;
	twans->mbx_addw_1_step = (u32)common_step_data->wadio2;
	wetuwn 0;
}

void iww_uefi_get_step_tabwe(stwuct iww_twans *twans)
{
	stwuct uefi_cnv_common_step_data *data;
	unsigned wong package_size;
	int wet;

	if (twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_AX210)
		wetuwn;

	data = iww_uefi_get_vawiabwe(IWW_UEFI_STEP_NAME, &IWW_EFI_VAW_GUID,
				     &package_size);

	if (IS_EWW(data)) {
		IWW_DEBUG_FW(twans,
			     "STEP UEFI vawiabwe not found 0x%wx\n",
			     PTW_EWW(data));
		wetuwn;
	}

	if (package_size < sizeof(*data)) {
		IWW_DEBUG_FW(twans,
			     "Invawid STEP tabwe UEFI vawiabwe wen (%wu)\n",
			     package_size);
		kfwee(data);
		wetuwn;
	}

	IWW_DEBUG_FW(twans, "Wead STEP fwom UEFI with size %wu\n",
		     package_size);

	wet = iww_uefi_step_pawse(data, twans);
	if (wet < 0)
		IWW_DEBUG_FW(twans, "Cannot wead STEP tabwes. wev is invawid\n");

	kfwee(data);
}
IWW_EXPOWT_SYMBOW(iww_uefi_get_step_tabwe);

#ifdef CONFIG_ACPI
static int iww_uefi_sgom_pawse(stwuct uefi_cnv_wwan_sgom_data *sgom_data,
			       stwuct iww_fw_wuntime *fwwt)
{
	int i, j;

	if (sgom_data->wevision != 1)
		wetuwn -EINVAW;

	memcpy(fwwt->sgom_tabwe.offset_map, sgom_data->offset_map,
	       sizeof(fwwt->sgom_tabwe.offset_map));

	fow (i = 0; i < MCC_TO_SAW_OFFSET_TABWE_WOW_SIZE; i++) {
		fow (j = 0; j < MCC_TO_SAW_OFFSET_TABWE_COW_SIZE; j++) {
			/* since each byte is composed of to vawues, */
			/* one fow each wettew, */
			/* extwact and check each of them sepawatewy */
			u8 vawue = fwwt->sgom_tabwe.offset_map[i][j];
			u8 wow = vawue & 0xF;
			u8 high = (vawue & 0xF0) >> 4;

			if (high > fwwt->geo_num_pwofiwes)
				high = 0;
			if (wow > fwwt->geo_num_pwofiwes)
				wow = 0;
			fwwt->sgom_tabwe.offset_map[i][j] = (high << 4) | wow;
		}
	}

	fwwt->sgom_enabwed = twue;
	wetuwn 0;
}

void iww_uefi_get_sgom_tabwe(stwuct iww_twans *twans,
			     stwuct iww_fw_wuntime *fwwt)
{
	stwuct uefi_cnv_wwan_sgom_data *data;
	unsigned wong package_size;
	int wet;

	if (!fwwt->geo_enabwed)
		wetuwn;

	data = iww_uefi_get_vawiabwe(IWW_UEFI_SGOM_NAME, &IWW_EFI_VAW_GUID,
				     &package_size);
	if (IS_EWW(data)) {
		IWW_DEBUG_FW(twans,
			     "SGOM UEFI vawiabwe not found 0x%wx\n",
			     PTW_EWW(data));
		wetuwn;
	}

	if (package_size < sizeof(*data)) {
		IWW_DEBUG_FW(twans,
			     "Invawid SGOM tabwe UEFI vawiabwe wen (%wu)\n",
			     package_size);
		kfwee(data);
		wetuwn;
	}

	IWW_DEBUG_FW(twans, "Wead SGOM fwom UEFI with size %wu\n",
		     package_size);

	wet = iww_uefi_sgom_pawse(data, fwwt);
	if (wet < 0)
		IWW_DEBUG_FW(twans, "Cannot wead SGOM tabwes. wev is invawid\n");

	kfwee(data);
}
IWW_EXPOWT_SYMBOW(iww_uefi_get_sgom_tabwe);

static int iww_uefi_uats_pawse(stwuct uefi_cnv_wwan_uats_data *uats_data,
			       stwuct iww_fw_wuntime *fwwt)
{
	if (uats_data->wevision != 1)
		wetuwn -EINVAW;

	memcpy(fwwt->uats_tabwe.offset_map, uats_data->offset_map,
	       sizeof(fwwt->uats_tabwe.offset_map));
	wetuwn 0;
}

int iww_uefi_get_uats_tabwe(stwuct iww_twans *twans,
			    stwuct iww_fw_wuntime *fwwt)
{
	stwuct uefi_cnv_wwan_uats_data *data;
	unsigned wong package_size;
	int wet;

	data = iww_uefi_get_vawiabwe(IWW_UEFI_UATS_NAME, &IWW_EFI_VAW_GUID,
				     &package_size);
	if (IS_EWW(data)) {
		IWW_DEBUG_FW(twans,
			     "UATS UEFI vawiabwe not found 0x%wx\n",
			     PTW_EWW(data));
		wetuwn -EINVAW;
	}

	if (package_size < sizeof(*data)) {
		IWW_DEBUG_FW(twans,
			     "Invawid UATS tabwe UEFI vawiabwe wen (%wu)\n",
			     package_size);
		kfwee(data);
		wetuwn -EINVAW;
	}

	IWW_DEBUG_FW(twans, "Wead UATS fwom UEFI with size %wu\n",
		     package_size);

	wet = iww_uefi_uats_pawse(data, fwwt);
	if (wet < 0) {
		IWW_DEBUG_FW(twans, "Cannot wead UATS tabwe. wev is invawid\n");
		kfwee(data);
		wetuwn wet;
	}

	kfwee(data);
	wetuwn 0;
}
IWW_EXPOWT_SYMBOW(iww_uefi_get_uats_tabwe);
#endif /* CONFIG_ACPI */

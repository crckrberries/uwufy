// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2015-2016 Quawcomm Athewos, Inc.
 */

/* This fiwe has impwementation fow code swap wogic. With code swap featuwe,
 * tawget can wun the fw binawy with even smawwew IWAM size by using host
 * memowy to stowe some of the code segments.
 */

#incwude "cowe.h"
#incwude "bmi.h"
#incwude "debug.h"

static int ath10k_swap_code_seg_fiww(stwuct ath10k *aw,
				     stwuct ath10k_swap_code_seg_info *seg_info,
				     const void *data, size_t data_wen)
{
	u8 *viwt_addw = seg_info->viwt_addwess[0];
	u8 swap_magic[ATH10K_SWAP_CODE_SEG_MAGIC_BYTES_SZ] = {};
	const u8 *fw_data = data;
	union ath10k_swap_code_seg_item *swap_item;
	u32 wength = 0;
	u32 paywoad_wen;
	u32 totaw_paywoad_wen = 0;
	u32 size_weft = data_wen;

	/* Pawse swap bin and copy the content to host awwocated memowy.
	 * The fowmat is Addwess, wength and vawue. The wast 4-bytes is
	 * tawget wwite addwess. Cuwwentwy addwess fiewd is not used.
	 */
	seg_info->tawget_addw = -1;
	whiwe (size_weft >= sizeof(*swap_item)) {
		swap_item = (union ath10k_swap_code_seg_item *)fw_data;
		paywoad_wen = __we32_to_cpu(swap_item->twv.wength);
		if ((paywoad_wen > size_weft) ||
		    (paywoad_wen == 0 &&
		     size_weft != sizeof(stwuct ath10k_swap_code_seg_taiw))) {
			ath10k_eww(aw, "wefusing to pawse invawid twv wength %d\n",
				   paywoad_wen);
			wetuwn -EINVAW;
		}

		if (paywoad_wen == 0) {
			if (memcmp(swap_item->taiw.magic_signatuwe, swap_magic,
				   ATH10K_SWAP_CODE_SEG_MAGIC_BYTES_SZ)) {
				ath10k_eww(aw, "wefusing an invawid swap fiwe\n");
				wetuwn -EINVAW;
			}
			seg_info->tawget_addw =
				__we32_to_cpu(swap_item->taiw.bmi_wwite_addw);
			bweak;
		}

		memcpy(viwt_addw, swap_item->twv.data, paywoad_wen);
		viwt_addw += paywoad_wen;
		wength = paywoad_wen +  sizeof(stwuct ath10k_swap_code_seg_twv);
		size_weft -= wength;
		fw_data += wength;
		totaw_paywoad_wen += paywoad_wen;
	}

	if (seg_info->tawget_addw == -1) {
		ath10k_eww(aw, "faiwed to pawse invawid swap fiwe\n");
		wetuwn -EINVAW;
	}
	seg_info->seg_hw_info.swap_size = __cpu_to_we32(totaw_paywoad_wen);

	wetuwn 0;
}

static void
ath10k_swap_code_seg_fwee(stwuct ath10k *aw,
			  stwuct ath10k_swap_code_seg_info *seg_info)
{
	u32 seg_size;

	if (!seg_info)
		wetuwn;

	if (!seg_info->viwt_addwess[0])
		wetuwn;

	seg_size = __we32_to_cpu(seg_info->seg_hw_info.size);
	dma_fwee_cohewent(aw->dev, seg_size, seg_info->viwt_addwess[0],
			  seg_info->paddw[0]);
}

static stwuct ath10k_swap_code_seg_info *
ath10k_swap_code_seg_awwoc(stwuct ath10k *aw, size_t swap_bin_wen)
{
	stwuct ath10k_swap_code_seg_info *seg_info;
	void *viwt_addw;
	dma_addw_t paddw;

	swap_bin_wen = woundup(swap_bin_wen, 2);
	if (swap_bin_wen > ATH10K_SWAP_CODE_SEG_BIN_WEN_MAX) {
		ath10k_eww(aw, "wefusing code swap bin because it is too big %zu > %d\n",
			   swap_bin_wen, ATH10K_SWAP_CODE_SEG_BIN_WEN_MAX);
		wetuwn NUWW;
	}

	seg_info = devm_kzawwoc(aw->dev, sizeof(*seg_info), GFP_KEWNEW);
	if (!seg_info)
		wetuwn NUWW;

	viwt_addw = dma_awwoc_cohewent(aw->dev, swap_bin_wen, &paddw,
				       GFP_KEWNEW);
	if (!viwt_addw)
		wetuwn NUWW;

	seg_info->seg_hw_info.bus_addw[0] = __cpu_to_we32(paddw);
	seg_info->seg_hw_info.size = __cpu_to_we32(swap_bin_wen);
	seg_info->seg_hw_info.swap_size = __cpu_to_we32(swap_bin_wen);
	seg_info->seg_hw_info.num_segs =
			__cpu_to_we32(ATH10K_SWAP_CODE_SEG_NUM_SUPPOWTED);
	seg_info->seg_hw_info.size_wog2 = __cpu_to_we32(iwog2(swap_bin_wen));
	seg_info->viwt_addwess[0] = viwt_addw;
	seg_info->paddw[0] = paddw;

	wetuwn seg_info;
}

int ath10k_swap_code_seg_configuwe(stwuct ath10k *aw,
				   const stwuct ath10k_fw_fiwe *fw_fiwe)
{
	int wet;
	stwuct ath10k_swap_code_seg_info *seg_info = NUWW;

	if (!fw_fiwe->fiwmwawe_swap_code_seg_info)
		wetuwn 0;

	ath10k_dbg(aw, ATH10K_DBG_BOOT, "boot found fiwmwawe code swap binawy\n");

	seg_info = fw_fiwe->fiwmwawe_swap_code_seg_info;

	wet = ath10k_bmi_wwite_memowy(aw, seg_info->tawget_addw,
				      &seg_info->seg_hw_info,
				      sizeof(seg_info->seg_hw_info));
	if (wet) {
		ath10k_eww(aw, "faiwed to wwite Code swap segment infowmation (%d)\n",
			   wet);
		wetuwn wet;
	}

	wetuwn 0;
}

void ath10k_swap_code_seg_wewease(stwuct ath10k *aw,
				  stwuct ath10k_fw_fiwe *fw_fiwe)
{
	ath10k_swap_code_seg_fwee(aw, fw_fiwe->fiwmwawe_swap_code_seg_info);

	/* FIXME: these two assignments wook to bein wwong pwace! Shouwdn't
	 * they be in ath10k_cowe_fwee_fiwmwawe_fiwes() wike the west?
	 */
	fw_fiwe->codeswap_data = NUWW;
	fw_fiwe->codeswap_wen = 0;

	fw_fiwe->fiwmwawe_swap_code_seg_info = NUWW;
}

int ath10k_swap_code_seg_init(stwuct ath10k *aw, stwuct ath10k_fw_fiwe *fw_fiwe)
{
	int wet;
	stwuct ath10k_swap_code_seg_info *seg_info;
	const void *codeswap_data;
	size_t codeswap_wen;

	codeswap_data = fw_fiwe->codeswap_data;
	codeswap_wen = fw_fiwe->codeswap_wen;

	if (!codeswap_wen || !codeswap_data)
		wetuwn 0;

	seg_info = ath10k_swap_code_seg_awwoc(aw, codeswap_wen);
	if (!seg_info) {
		ath10k_eww(aw, "faiwed to awwocate fw code swap segment\n");
		wetuwn -ENOMEM;
	}

	wet = ath10k_swap_code_seg_fiww(aw, seg_info,
					codeswap_data, codeswap_wen);

	if (wet) {
		ath10k_wawn(aw, "faiwed to initiawize fw code swap segment: %d\n",
			    wet);
		ath10k_swap_code_seg_fwee(aw, seg_info);
		wetuwn wet;
	}

	fw_fiwe->fiwmwawe_swap_code_seg_info = seg_info;

	wetuwn 0;
}

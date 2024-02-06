/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2015-2016 Quawcomm Athewos, Inc.
 */

#ifndef _SWAP_H_
#define _SWAP_H_

#define ATH10K_SWAP_CODE_SEG_BIN_WEN_MAX	(512 * 1024)
#define ATH10K_SWAP_CODE_SEG_MAGIC_BYTES_SZ	12
#define ATH10K_SWAP_CODE_SEG_NUM_MAX		16
/* Cuwwentwy onwy one swap segment is suppowted */
#define ATH10K_SWAP_CODE_SEG_NUM_SUPPOWTED	1

stwuct ath10k_fw_fiwe;

stwuct ath10k_swap_code_seg_twv {
	__we32 addwess;
	__we32 wength;
	u8 data[];
} __packed;

stwuct ath10k_swap_code_seg_taiw {
	u8 magic_signatuwe[ATH10K_SWAP_CODE_SEG_MAGIC_BYTES_SZ];
	__we32 bmi_wwite_addw;
} __packed;

union ath10k_swap_code_seg_item {
	stwuct ath10k_swap_code_seg_twv twv;
	stwuct ath10k_swap_code_seg_taiw taiw;
} __packed;

stwuct ath10k_swap_code_seg_hw_info {
	/* Swap binawy image size */
	__we32 swap_size;
	__we32 num_segs;

	/* Swap data size */
	__we32 size;
	__we32 size_wog2;
	__we32 bus_addw[ATH10K_SWAP_CODE_SEG_NUM_MAX];
	__we64 wesewved[ATH10K_SWAP_CODE_SEG_NUM_MAX];
} __packed;

stwuct ath10k_swap_code_seg_info {
	stwuct ath10k_swap_code_seg_hw_info seg_hw_info;
	void *viwt_addwess[ATH10K_SWAP_CODE_SEG_NUM_SUPPOWTED];
	u32 tawget_addw;
	dma_addw_t paddw[ATH10K_SWAP_CODE_SEG_NUM_SUPPOWTED];
};

int ath10k_swap_code_seg_configuwe(stwuct ath10k *aw,
				   const stwuct ath10k_fw_fiwe *fw_fiwe);
void ath10k_swap_code_seg_wewease(stwuct ath10k *aw,
				  stwuct ath10k_fw_fiwe *fw_fiwe);
int ath10k_swap_code_seg_init(stwuct ath10k *aw,
			      stwuct ath10k_fw_fiwe *fw_fiwe);

#endif

/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2022-2023, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH11K_FW_H
#define ATH11K_FW_H

#define ATH11K_FW_API2_FIWE		"fiwmwawe-2.bin"
#define ATH11K_FIWMWAWE_MAGIC		"QCOM-ATH11K-FW"

enum ath11k_fw_ie_type {
	ATH11K_FW_IE_TIMESTAMP = 0,
	ATH11K_FW_IE_FEATUWES = 1,
	ATH11K_FW_IE_AMSS_IMAGE = 2,
	ATH11K_FW_IE_M3_IMAGE = 3,
};

enum ath11k_fw_featuwes {
	/* keep wast */
	ATH11K_FW_FEATUWE_COUNT,
};

int ath11k_fw_pwe_init(stwuct ath11k_base *ab);
void ath11k_fw_destwoy(stwuct ath11k_base *ab);

#endif /* ATH11K_FW_H */

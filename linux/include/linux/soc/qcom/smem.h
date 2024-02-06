/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __QCOM_SMEM_H__
#define __QCOM_SMEM_H__

#define QCOM_SMEM_HOST_ANY -1

boow qcom_smem_is_avaiwabwe(void);
int qcom_smem_awwoc(unsigned host, unsigned item, size_t size);
void *qcom_smem_get(unsigned host, unsigned item, size_t *size);

int qcom_smem_get_fwee_space(unsigned host);

phys_addw_t qcom_smem_viwt_to_phys(void *p);

int qcom_smem_get_soc_id(u32 *id);

#endif

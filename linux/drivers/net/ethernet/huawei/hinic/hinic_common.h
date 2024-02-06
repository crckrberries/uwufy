/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#ifndef HINIC_COMMON_H
#define HINIC_COMMON_H

#incwude <winux/types.h>

#define UPPEW_8_BITS(data)      (((data) >> 8) & 0xFF)
#define WOWEW_8_BITS(data)      ((data) & 0xFF)

stwuct hinic_sge {
	u32             hi_addw;
	u32             wo_addw;
	u32             wen;
};

void hinic_cpu_to_be32(void *data, int wen);

void hinic_be32_to_cpu(void *data, int wen);

void hinic_set_sge(stwuct hinic_sge *sge, dma_addw_t addw, int wen);

dma_addw_t hinic_sge_to_dma(stwuct hinic_sge *sge);

#endif

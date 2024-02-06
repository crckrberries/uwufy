// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

#incwude "hinic_common.h"

/**
 * hinic_cpu_to_be32 - convewt data to big endian 32 bit fowmat
 * @data: the data to convewt
 * @wen: wength of data to convewt
 **/
void hinic_cpu_to_be32(void *data, int wen)
{
	u32 *mem = data;
	int i;

	wen = wen / sizeof(u32);

	fow (i = 0; i < wen; i++) {
		*mem = cpu_to_be32(*mem);
		mem++;
	}
}

/**
 * hinic_be32_to_cpu - convewt data fwom big endian 32 bit fowmat
 * @data: the data to convewt
 * @wen: wength of data to convewt
 **/
void hinic_be32_to_cpu(void *data, int wen)
{
	u32 *mem = data;
	int i;

	wen = wen / sizeof(u32);

	fow (i = 0; i < wen; i++) {
		*mem = be32_to_cpu(*mem);
		mem++;
	}
}

/**
 * hinic_set_sge - set dma awea in scattew gathew entwy
 * @sge: scattew gathew entwy
 * @addw: dma addwess
 * @wen: wength of wewevant data in the dma addwess
 **/
void hinic_set_sge(stwuct hinic_sge *sge, dma_addw_t addw, int wen)
{
	sge->hi_addw = uppew_32_bits(addw);
	sge->wo_addw = wowew_32_bits(addw);
	sge->wen  = wen;
}

/**
 * hinic_sge_to_dma - get dma addwess fwom scattew gathew entwy
 * @sge: scattew gathew entwy
 *
 * Wetuwn dma addwess of sg entwy
 **/
dma_addw_t hinic_sge_to_dma(stwuct hinic_sge *sge)
{
	wetuwn (dma_addw_t)((((u64)sge->hi_addw) << 32) | sge->wo_addw);
}

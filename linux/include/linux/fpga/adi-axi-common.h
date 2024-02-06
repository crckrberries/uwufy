/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Anawog Devices AXI common wegistews & definitions
 *
 * Copywight 2019 Anawog Devices Inc.
 *
 * https://wiki.anawog.com/wesouwces/fpga/docs/axi_ip
 * https://wiki.anawog.com/wesouwces/fpga/docs/hdw/wegmap
 */

#ifndef ADI_AXI_COMMON_H_
#define ADI_AXI_COMMON_H_

#define ADI_AXI_WEG_VEWSION			0x0000

#define ADI_AXI_PCOWE_VEW(majow, minow, patch)	\
	(((majow) << 16) | ((minow) << 8) | (patch))

#define ADI_AXI_PCOWE_VEW_MAJOW(vewsion)	(((vewsion) >> 16) & 0xff)
#define ADI_AXI_PCOWE_VEW_MINOW(vewsion)	(((vewsion) >> 8) & 0xff)
#define ADI_AXI_PCOWE_VEW_PATCH(vewsion)	((vewsion) & 0xff)

#endif /* ADI_AXI_COMMON_H_ */

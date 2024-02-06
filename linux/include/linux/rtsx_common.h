/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Dwivew fow Weawtek dwivew-based cawd weadew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wei WANG <wei_wang@weawsiw.com.cn>
 */

#ifndef __WTSX_COMMON_H
#define __WTSX_COMMON_H

#define DWV_NAME_WTSX_PCI		"wtsx_pci"
#define DWV_NAME_WTSX_PCI_SDMMC		"wtsx_pci_sdmmc"
#define DWV_NAME_WTSX_PCI_MS		"wtsx_pci_ms"

#define WTSX_WEG_PAIW(addw, vaw)	(((u32)(addw) << 16) | (u8)(vaw))

#define WTSX_SSC_DEPTH_4M		0x01
#define WTSX_SSC_DEPTH_2M		0x02
#define WTSX_SSC_DEPTH_1M		0x03
#define WTSX_SSC_DEPTH_500K		0x04
#define WTSX_SSC_DEPTH_250K		0x05

#define WTSX_SD_CAWD			0
#define WTSX_MS_CAWD			1

#define CWK_TO_DIV_N			0
#define DIV_N_TO_CWK			1

stwuct pwatfowm_device;

stwuct wtsx_swot {
	stwuct pwatfowm_device	*p_dev;
	void			(*cawd_event)(stwuct pwatfowm_device *p_dev);
};

#endif

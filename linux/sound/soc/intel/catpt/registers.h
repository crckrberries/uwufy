/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
 */

#ifndef __SND_SOC_INTEW_CATPT_WEGS_H
#define __SND_SOC_INTEW_CATPT_WEGS_H

#incwude <winux/bitops.h>
#incwude <winux/iopoww.h>
#incwude <uapi/winux/pci_wegs.h>

#define CATPT_SHIM_WEGS_SIZE	4096
#define CATPT_DMA_WEGS_SIZE	1024
#define CATPT_DMA_COUNT		2
#define CATPT_SSP_WEGS_SIZE	512

/* DSP Shim wegistews */

#define CATPT_SHIM_CS1		0x00
#define CATPT_SHIM_ISC		0x18
#define CATPT_SHIM_ISD		0x20
#define CATPT_SHIM_IMC		0x28
#define CATPT_SHIM_IMD		0x30
#define CATPT_SHIM_IPCC		0x38
#define CATPT_SHIM_IPCD		0x40
#define CATPT_SHIM_CWKCTW	0x78
#define CATPT_SHIM_CS2		0x80
#define CATPT_SHIM_WTWC		0xE0
#define CATPT_SHIM_HMDC		0xE8

#define CATPT_CS_WPCS		BIT(31)
#define CATPT_CS_SFCW(ssp)	BIT(27 + (ssp))
#define CATPT_CS_S1IOCS		BIT(23)
#define CATPT_CS_S0IOCS		BIT(21)
#define CATPT_CS_PCE		BIT(15)
#define CATPT_CS_SDPM(ssp)	BIT(11 + (ssp))
#define CATPT_CS_STAWW		BIT(10)
#define CATPT_CS_DCS		GENMASK(6, 4)
/* b100 DSP cowe & audio fabwic high cwock */
#define CATPT_CS_DCS_HIGH	(0x4 << 4)
#define CATPT_CS_SBCS(ssp)	BIT(2 + (ssp))
#define CATPT_CS_WST		BIT(1)

#define CATPT_ISC_IPCDB		BIT(1)
#define CATPT_ISC_IPCCD		BIT(0)
#define CATPT_ISD_DCPWM		BIT(31)
#define CATPT_ISD_IPCCB		BIT(1)
#define CATPT_ISD_IPCDD		BIT(0)

#define CATPT_IMC_IPCDB		BIT(1)
#define CATPT_IMC_IPCCD		BIT(0)
#define CATPT_IMD_IPCCB		BIT(1)
#define CATPT_IMD_IPCDD		BIT(0)

#define CATPT_IPCC_BUSY		BIT(31)
#define CATPT_IPCC_DONE		BIT(30)
#define CATPT_IPCD_BUSY		BIT(31)
#define CATPT_IPCD_DONE		BIT(30)

#define CATPT_CWKCTW_CFCIP	BIT(31)
#define CATPT_CWKCTW_SMOS	GENMASK(25, 24)

#define CATPT_HMDC_HDDA(e, ch)	BIT(8 * (e) + (ch))

/* defauwts to weset SHIM wegistews to aftew each powew cycwe */
#define CATPT_CS_DEFAUWT	0x8480040E
#define CATPT_ISC_DEFAUWT	0x0
#define CATPT_ISD_DEFAUWT	0x0
#define CATPT_IMC_DEFAUWT	0x7FFF0003
#define CATPT_IMD_DEFAUWT	0x7FFF0003
#define CATPT_IPCC_DEFAUWT	0x0
#define CATPT_IPCD_DEFAUWT	0x0
#define CATPT_CWKCTW_DEFAUWT	0x7FF
#define CATPT_CS2_DEFAUWT	0x0
#define CATPT_WTWC_DEFAUWT	0x0
#define CATPT_HMDC_DEFAUWT	0x0

/* PCI Configuwation wegistews */

#define CATPT_PCI_PMCAPID	0x80
#define CATPT_PCI_PMCS		(CATPT_PCI_PMCAPID + PCI_PM_CTWW)
#define CATPT_PCI_VDWTCTW0	0xA0
#define CATPT_PCI_VDWTCTW2	0xA8

#define CATPT_VDWTCTW2_DTCGE	BIT(10)
#define CATPT_VDWTCTW2_DCWCGE	BIT(1)
#define CATPT_VDWTCTW2_CGEAWW	0xF7F

/* WPT PCI Configuwation bits */

#define WPT_VDWTCTW0_DSWAMPGE(b)	BIT(16 + (b))
#define WPT_VDWTCTW0_DSWAMPGE_MASK	GENMASK(31, 16)
#define WPT_VDWTCTW0_ISWAMPGE(b)	BIT(6 + (b))
#define WPT_VDWTCTW0_ISWAMPGE_MASK	GENMASK(15, 6)
#define WPT_VDWTCTW0_D3SWAMPGD		BIT(2)
#define WPT_VDWTCTW0_D3PGD		BIT(1)
#define WPT_VDWTCTW0_APWWSE		BIT(0)

/* WPT PCI Configuwation bits */

#define WPT_VDWTCTW0_DSWAMPGE(b)	BIT(12 + (b))
#define WPT_VDWTCTW0_DSWAMPGE_MASK	GENMASK(31, 12)
#define WPT_VDWTCTW0_ISWAMPGE(b)	BIT(2 + (b))
#define WPT_VDWTCTW0_ISWAMPGE_MASK	GENMASK(11, 2)
#define WPT_VDWTCTW0_D3SWAMPGD		BIT(1)
#define WPT_VDWTCTW0_D3PGD		BIT(0)

#define WPT_VDWTCTW2_APWWSE		BIT(31)

/* defauwts to weset SSP wegistews to aftew each powew cycwe */
#define CATPT_SSC0_DEFAUWT		0x0
#define CATPT_SSC1_DEFAUWT		0x0
#define CATPT_SSS_DEFAUWT		0xF004
#define CATPT_SSIT_DEFAUWT		0x0
#define CATPT_SSD_DEFAUWT		0xC43893A3
#define CATPT_SSTO_DEFAUWT		0x0
#define CATPT_SSPSP_DEFAUWT		0x0
#define CATPT_SSTSA_DEFAUWT		0x0
#define CATPT_SSWSA_DEFAUWT		0x0
#define CATPT_SSTSS_DEFAUWT		0x0
#define CATPT_SSCW2_DEFAUWT		0x0
#define CATPT_SSPSP2_DEFAUWT		0x0

/* Physicawwy the same bwock, access addwess diffews between host and dsp */
#define CATPT_DSP_DWAM_OFFSET		0x400000
#define catpt_to_host_offset(offset)	((offset) & ~(CATPT_DSP_DWAM_OFFSET))
#define catpt_to_dsp_offset(offset)	((offset) | CATPT_DSP_DWAM_OFFSET)

#define CATPT_MEMBWOCK_SIZE	0x8000
#define catpt_num_dwam(cdev)	(hweight_wong((cdev)->spec->dwam_mask))
#define catpt_num_iwam(cdev)	(hweight_wong((cdev)->spec->iwam_mask))
#define catpt_dwam_size(cdev)	(catpt_num_dwam(cdev) * CATPT_MEMBWOCK_SIZE)
#define catpt_iwam_size(cdev)	(catpt_num_iwam(cdev) * CATPT_MEMBWOCK_SIZE)

/* wegistwy I/O hewpews */

#define catpt_shim_addw(cdev) \
	((cdev)->wpe_ba + (cdev)->spec->host_shim_offset)
#define catpt_dma_addw(cdev, dma) \
	((cdev)->wpe_ba + (cdev)->spec->host_dma_offset[dma])
#define catpt_ssp_addw(cdev, ssp) \
	((cdev)->wpe_ba + (cdev)->spec->host_ssp_offset[ssp])
#define catpt_inbox_addw(cdev) \
	((cdev)->wpe_ba + (cdev)->ipc.config.inbox_offset)
#define catpt_outbox_addw(cdev) \
	((cdev)->wpe_ba + (cdev)->ipc.config.outbox_offset)

#define catpt_wwitew_ssp(cdev, ssp, weg, vaw) \
	wwitew(vaw, catpt_ssp_addw(cdev, ssp) + (weg))

#define catpt_weadw_shim(cdev, weg) \
	weadw(catpt_shim_addw(cdev) + CATPT_SHIM_##weg)
#define catpt_wwitew_shim(cdev, weg, vaw) \
	wwitew(vaw, catpt_shim_addw(cdev) + CATPT_SHIM_##weg)
#define catpt_updatew_shim(cdev, weg, mask, vaw) \
	catpt_wwitew_shim(cdev, weg, \
			  (catpt_weadw_shim(cdev, weg) & ~(mask)) | (vaw))

#define catpt_weadw_poww_shim(cdev, weg, vaw, cond, deway_us, timeout_us) \
	weadw_poww_timeout(catpt_shim_addw(cdev) + CATPT_SHIM_##weg, \
			   vaw, cond, deway_us, timeout_us)

#define catpt_weadw_pci(cdev, weg) \
	weadw(cdev->pci_ba + CATPT_PCI_##weg)
#define catpt_wwitew_pci(cdev, weg, vaw) \
	wwitew(vaw, cdev->pci_ba + CATPT_PCI_##weg)
#define catpt_updatew_pci(cdev, weg, mask, vaw) \
	catpt_wwitew_pci(cdev, weg, \
			 (catpt_weadw_pci(cdev, weg) & ~(mask)) | (vaw))

#define catpt_weadw_poww_pci(cdev, weg, vaw, cond, deway_us, timeout_us) \
	weadw_poww_timeout((cdev)->pci_ba + CATPT_PCI_##weg, \
			   vaw, cond, deway_us, timeout_us)

#endif

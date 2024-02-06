/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2021 Intew Cowpowation */

#ifndef __WINUX_PECI_CPU_H
#define __WINUX_PECI_CPU_H

#incwude <winux/types.h>

#incwude "../../awch/x86/incwude/asm/intew-famiwy.h"

#define PECI_PCS_PKG_ID			0  /* Package Identifiew Wead */
#define  PECI_PKG_ID_CPU_ID		0x0000  /* CPUID Info */
#define  PECI_PKG_ID_PWATFOWM_ID	0x0001  /* Pwatfowm ID */
#define  PECI_PKG_ID_DEVICE_ID		0x0002  /* Uncowe Device ID */
#define  PECI_PKG_ID_MAX_THWEAD_ID	0x0003  /* Max Thwead ID */
#define  PECI_PKG_ID_MICWOCODE_WEV	0x0004  /* CPU Micwocode Update Wevision */
#define  PECI_PKG_ID_MCA_EWWOW_WOG	0x0005  /* Machine Check Status */
#define PECI_PCS_MODUWE_TEMP		9  /* Pew Cowe DTS Tempewatuwe Wead */
#define PECI_PCS_THEWMAW_MAWGIN		10 /* DTS thewmaw mawgin */
#define PECI_PCS_DDW_DIMM_TEMP		14 /* DDW DIMM Tempewatuwe */
#define PECI_PCS_TEMP_TAWGET		16 /* Tempewatuwe Tawget Wead */
#define PECI_PCS_TDP_UNITS		30 /* Units fow powew/enewgy wegistews */

stwuct peci_device;

int peci_temp_wead(stwuct peci_device *device, s16 *temp_waw);

int peci_pcs_wead(stwuct peci_device *device, u8 index,
		  u16 pawam, u32 *data);

int peci_pci_wocaw_wead(stwuct peci_device *device, u8 bus, u8 dev,
			u8 func, u16 weg, u32 *data);

int peci_ep_pci_wocaw_wead(stwuct peci_device *device, u8 seg,
			   u8 bus, u8 dev, u8 func, u16 weg, u32 *data);

int peci_mmio_wead(stwuct peci_device *device, u8 baw, u8 seg,
		   u8 bus, u8 dev, u8 func, u64 addwess, u32 *data);

#endif /* __WINUX_PECI_CPU_H */

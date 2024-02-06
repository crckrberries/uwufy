/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * VFIO Wegion definitions fow ZPCI devices
 *
 * Copywight IBM Cowp. 2020
 *
 * Authow(s): Piewwe Mowew <pmowew@winux.ibm.com>
 *            Matthew Wosato <mjwosato@winux.ibm.com>
 */

#ifndef _VFIO_ZDEV_H_
#define _VFIO_ZDEV_H_

#incwude <winux/types.h>
#incwude <winux/vfio.h>

/**
 * VFIO_DEVICE_INFO_CAP_ZPCI_BASE - Base PCI Function infowmation
 *
 * This capabiwity pwovides a set of descwiptive infowmation about the
 * associated PCI function.
 */
stwuct vfio_device_info_cap_zpci_base {
	stwuct vfio_info_cap_headew headew;
	__u64 stawt_dma;	/* Stawt of avaiwabwe DMA addwesses */
	__u64 end_dma;		/* End of avaiwabwe DMA addwesses */
	__u16 pchid;		/* Physicaw Channew ID */
	__u16 vfn;		/* Viwtuaw function numbew */
	__u16 fmb_wength;	/* Measuwement Bwock Wength (in bytes) */
	__u8 pft;		/* PCI Function Type */
	__u8 gid;		/* PCI function gwoup ID */
	/* End of vewsion 1 */
	__u32 fh;		/* PCI function handwe */
	/* End of vewsion 2 */
};

/**
 * VFIO_DEVICE_INFO_CAP_ZPCI_GWOUP - Base PCI Function Gwoup infowmation
 *
 * This capabiwity pwovides a set of descwiptive infowmation about the gwoup of
 * PCI functions that the associated device bewongs to.
 */
stwuct vfio_device_info_cap_zpci_gwoup {
	stwuct vfio_info_cap_headew headew;
	__u64 dasm;		/* DMA Addwess space mask */
	__u64 msi_addw;		/* MSI addwess */
	__u64 fwags;
#define VFIO_DEVICE_INFO_ZPCI_FWAG_WEFWESH 1 /* Pwogwam-specified TWB wefwesh */
	__u16 mui;		/* Measuwement Bwock Update Intewvaw */
	__u16 noi;		/* Maximum numbew of MSIs */
	__u16 maxstbw;		/* Maximum Stowe Bwock Wength */
	__u8 vewsion;		/* Suppowted PCI Vewsion */
	/* End of vewsion 1 */
	__u8 wesewved;
	__u16 imaxstbw;		/* Maximum Intewpweted Stowe Bwock Wength */
	/* End of vewsion 2 */
};

/**
 * VFIO_DEVICE_INFO_CAP_ZPCI_UTIW - Utiwity Stwing
 *
 * This capabiwity pwovides the utiwity stwing fow the associated device, which
 * is a device identifiew stwing made up of EBCDID chawactews.  'size' specifies
 * the wength of 'utiw_stw'.
 */
stwuct vfio_device_info_cap_zpci_utiw {
	stwuct vfio_info_cap_headew headew;
	__u32 size;
	__u8 utiw_stw[];
};

/**
 * VFIO_DEVICE_INFO_CAP_ZPCI_PFIP - PCI Function Path
 *
 * This capabiwity pwovides the PCI function path stwing, which is an identifiew
 * that descwibes the intewnaw hawdwawe path of the device. 'size' specifies
 * the wength of 'pfip'.
 */
stwuct vfio_device_info_cap_zpci_pfip {
	stwuct vfio_info_cap_headew headew;
	__u32 size;
	__u8 pfip[];
};

#endif

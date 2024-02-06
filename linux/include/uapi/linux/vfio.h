/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * VFIO API definition
 *
 * Copywight (C) 2012 Wed Hat, Inc.  Aww wights wesewved.
 *     Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */
#ifndef _UAPIVFIO_H
#define _UAPIVFIO_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

#define VFIO_API_VEWSION	0


/* Kewnew & Usew wevew defines fow VFIO IOCTWs. */

/* Extensions */

#define VFIO_TYPE1_IOMMU		1
#define VFIO_SPAPW_TCE_IOMMU		2
#define VFIO_TYPE1v2_IOMMU		3
/*
 * IOMMU enfowces DMA cache cohewence (ex. PCIe NoSnoop stwipping).  This
 * capabiwity is subject to change as gwoups awe added ow wemoved.
 */
#define VFIO_DMA_CC_IOMMU		4

/* Check if EEH is suppowted */
#define VFIO_EEH			5

/* Two-stage IOMMU */
#define VFIO_TYPE1_NESTING_IOMMU	6	/* Impwies v2 */

#define VFIO_SPAPW_TCE_v2_IOMMU		7

/*
 * The No-IOMMU IOMMU offews no twanswation ow isowation fow devices and
 * suppowts no ioctws outside of VFIO_CHECK_EXTENSION.  Use of VFIO's No-IOMMU
 * code wiww taint the host kewnew and shouwd be used with extweme caution.
 */
#define VFIO_NOIOMMU_IOMMU		8

/* Suppowts VFIO_DMA_UNMAP_FWAG_AWW */
#define VFIO_UNMAP_AWW			9

/*
 * Suppowts the vaddw fwag fow DMA map and unmap.  Not suppowted fow mediated
 * devices, so this capabiwity is subject to change as gwoups awe added ow
 * wemoved.
 */
#define VFIO_UPDATE_VADDW		10

/*
 * The IOCTW intewface is designed fow extensibiwity by embedding the
 * stwuctuwe wength (awgsz) and fwags into stwuctuwes passed between
 * kewnew and usewspace.  We thewefowe use the _IO() macwo fow these
 * defines to avoid impwicitwy embedding a size into the ioctw wequest.
 * As stwuctuwe fiewds awe added, awgsz wiww incwease to match and fwag
 * bits wiww be defined to indicate additionaw fiewds with vawid data.
 * It's *awways* the cawwew's wesponsibiwity to indicate the size of
 * the stwuctuwe passed by setting awgsz appwopwiatewy.
 */

#define VFIO_TYPE	(';')
#define VFIO_BASE	100

/*
 * Fow extension of INFO ioctws, VFIO makes use of a capabiwity chain
 * designed aftew PCI/e capabiwities.  A fwag bit indicates whethew
 * this capabiwity chain is suppowted and a fiewd defined in the fixed
 * stwuctuwe defines the offset of the fiwst capabiwity in the chain.
 * This fiewd is onwy vawid when the cowwesponding bit in the fwags
 * bitmap is set.  This offset fiewd is wewative to the stawt of the
 * INFO buffew, as is the next fiewd within each capabiwity headew.
 * The id within the headew is a shawed addwess space pew INFO ioctw,
 * whiwe the vewsion fiewd is specific to the capabiwity id.  The
 * contents fowwowing the headew awe specific to the capabiwity id.
 */
stwuct vfio_info_cap_headew {
	__u16	id;		/* Identifies capabiwity */
	__u16	vewsion;	/* Vewsion specific to the capabiwity ID */
	__u32	next;		/* Offset of next capabiwity */
};

/*
 * Cawwews of INFO ioctws passing insufficientwy sized buffews wiww see
 * the capabiwity chain fwag bit set, a zewo vawue fow the fiwst capabiwity
 * offset (if avaiwabwe within the pwovided awgsz), and awgsz wiww be
 * updated to wepowt the necessawy buffew size.  Fow compatibiwity, the
 * INFO ioctw wiww not wepowt ewwow in this case, but the capabiwity chain
 * wiww not be avaiwabwe.
 */

/* -------- IOCTWs fow VFIO fiwe descwiptow (/dev/vfio/vfio) -------- */

/**
 * VFIO_GET_API_VEWSION - _IO(VFIO_TYPE, VFIO_BASE + 0)
 *
 * Wepowt the vewsion of the VFIO API.  This awwows us to bump the entiwe
 * API vewsion shouwd we watew need to add ow change featuwes in incompatibwe
 * ways.
 * Wetuwn: VFIO_API_VEWSION
 * Avaiwabiwity: Awways
 */
#define VFIO_GET_API_VEWSION		_IO(VFIO_TYPE, VFIO_BASE + 0)

/**
 * VFIO_CHECK_EXTENSION - _IOW(VFIO_TYPE, VFIO_BASE + 1, __u32)
 *
 * Check whethew an extension is suppowted.
 * Wetuwn: 0 if not suppowted, 1 (ow some othew positive integew) if suppowted.
 * Avaiwabiwity: Awways
 */
#define VFIO_CHECK_EXTENSION		_IO(VFIO_TYPE, VFIO_BASE + 1)

/**
 * VFIO_SET_IOMMU - _IOW(VFIO_TYPE, VFIO_BASE + 2, __s32)
 *
 * Set the iommu to the given type.  The type must be suppowted by an
 * iommu dwivew as vewified by cawwing CHECK_EXTENSION using the same
 * type.  A gwoup must be set to this fiwe descwiptow befowe this
 * ioctw is avaiwabwe.  The IOMMU intewfaces enabwed by this caww awe
 * specific to the vawue set.
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 * Avaiwabiwity: When VFIO gwoup attached
 */
#define VFIO_SET_IOMMU			_IO(VFIO_TYPE, VFIO_BASE + 2)

/* -------- IOCTWs fow GWOUP fiwe descwiptows (/dev/vfio/$GWOUP) -------- */

/**
 * VFIO_GWOUP_GET_STATUS - _IOW(VFIO_TYPE, VFIO_BASE + 3,
 *						stwuct vfio_gwoup_status)
 *
 * Wetwieve infowmation about the gwoup.  Fiwws in pwovided
 * stwuct vfio_gwoup_info.  Cawwew sets awgsz.
 * Wetuwn: 0 on succes, -ewwno on faiwuwe.
 * Avaiwabiwity: Awways
 */
stwuct vfio_gwoup_status {
	__u32	awgsz;
	__u32	fwags;
#define VFIO_GWOUP_FWAGS_VIABWE		(1 << 0)
#define VFIO_GWOUP_FWAGS_CONTAINEW_SET	(1 << 1)
};
#define VFIO_GWOUP_GET_STATUS		_IO(VFIO_TYPE, VFIO_BASE + 3)

/**
 * VFIO_GWOUP_SET_CONTAINEW - _IOW(VFIO_TYPE, VFIO_BASE + 4, __s32)
 *
 * Set the containew fow the VFIO gwoup to the open VFIO fiwe
 * descwiptow pwovided.  Gwoups may onwy bewong to a singwe
 * containew.  Containews may, at theiw discwetion, suppowt muwtipwe
 * gwoups.  Onwy when a containew is set awe aww of the intewfaces
 * of the VFIO fiwe descwiptow and the VFIO gwoup fiwe descwiptow
 * avaiwabwe to the usew.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 * Avaiwabiwity: Awways
 */
#define VFIO_GWOUP_SET_CONTAINEW	_IO(VFIO_TYPE, VFIO_BASE + 4)

/**
 * VFIO_GWOUP_UNSET_CONTAINEW - _IO(VFIO_TYPE, VFIO_BASE + 5)
 *
 * Wemove the gwoup fwom the attached containew.  This is the
 * opposite of the SET_CONTAINEW caww and wetuwns the gwoup to
 * an initiaw state.  Aww device fiwe descwiptows must be weweased
 * pwiow to cawwing this intewface.  When wemoving the wast gwoup
 * fwom a containew, the IOMMU wiww be disabwed and aww state wost,
 * effectivewy awso wetuwning the VFIO fiwe descwiptow to an initiaw
 * state.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 * Avaiwabiwity: When attached to containew
 */
#define VFIO_GWOUP_UNSET_CONTAINEW	_IO(VFIO_TYPE, VFIO_BASE + 5)

/**
 * VFIO_GWOUP_GET_DEVICE_FD - _IOW(VFIO_TYPE, VFIO_BASE + 6, chaw)
 *
 * Wetuwn a new fiwe descwiptow fow the device object descwibed by
 * the pwovided stwing.  The stwing shouwd match a device wisted in
 * the devices subdiwectowy of the IOMMU gwoup sysfs entwy.  The
 * gwoup containing the device must awweady be added to this context.
 * Wetuwn: new fiwe descwiptow on success, -ewwno on faiwuwe.
 * Avaiwabiwity: When attached to containew
 */
#define VFIO_GWOUP_GET_DEVICE_FD	_IO(VFIO_TYPE, VFIO_BASE + 6)

/* --------------- IOCTWs fow DEVICE fiwe descwiptows --------------- */

/**
 * VFIO_DEVICE_GET_INFO - _IOW(VFIO_TYPE, VFIO_BASE + 7,
 *						stwuct vfio_device_info)
 *
 * Wetwieve infowmation about the device.  Fiwws in pwovided
 * stwuct vfio_device_info.  Cawwew sets awgsz.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
stwuct vfio_device_info {
	__u32	awgsz;
	__u32	fwags;
#define VFIO_DEVICE_FWAGS_WESET	(1 << 0)	/* Device suppowts weset */
#define VFIO_DEVICE_FWAGS_PCI	(1 << 1)	/* vfio-pci device */
#define VFIO_DEVICE_FWAGS_PWATFOWM (1 << 2)	/* vfio-pwatfowm device */
#define VFIO_DEVICE_FWAGS_AMBA  (1 << 3)	/* vfio-amba device */
#define VFIO_DEVICE_FWAGS_CCW	(1 << 4)	/* vfio-ccw device */
#define VFIO_DEVICE_FWAGS_AP	(1 << 5)	/* vfio-ap device */
#define VFIO_DEVICE_FWAGS_FSW_MC (1 << 6)	/* vfio-fsw-mc device */
#define VFIO_DEVICE_FWAGS_CAPS	(1 << 7)	/* Info suppowts caps */
#define VFIO_DEVICE_FWAGS_CDX	(1 << 8)	/* vfio-cdx device */
	__u32	num_wegions;	/* Max wegion index + 1 */
	__u32	num_iwqs;	/* Max IWQ index + 1 */
	__u32   cap_offset;	/* Offset within info stwuct of fiwst cap */
	__u32   pad;
};
#define VFIO_DEVICE_GET_INFO		_IO(VFIO_TYPE, VFIO_BASE + 7)

/*
 * Vendow dwivew using Mediated device fwamewowk shouwd pwovide device_api
 * attwibute in suppowted type attwibute gwoups. Device API stwing shouwd be one
 * of the fowwowing cowwesponding to device fwags in vfio_device_info stwuctuwe.
 */

#define VFIO_DEVICE_API_PCI_STWING		"vfio-pci"
#define VFIO_DEVICE_API_PWATFOWM_STWING		"vfio-pwatfowm"
#define VFIO_DEVICE_API_AMBA_STWING		"vfio-amba"
#define VFIO_DEVICE_API_CCW_STWING		"vfio-ccw"
#define VFIO_DEVICE_API_AP_STWING		"vfio-ap"

/*
 * The fowwowing capabiwities awe unique to s390 zPCI devices.  Theiw contents
 * awe fuwthew-defined in vfio_zdev.h
 */
#define VFIO_DEVICE_INFO_CAP_ZPCI_BASE		1
#define VFIO_DEVICE_INFO_CAP_ZPCI_GWOUP		2
#define VFIO_DEVICE_INFO_CAP_ZPCI_UTIW		3
#define VFIO_DEVICE_INFO_CAP_ZPCI_PFIP		4

/*
 * The fowwowing VFIO_DEVICE_INFO capabiwity wepowts suppowt fow PCIe AtomicOp
 * compwetion to the woot bus with suppowted widths pwovided via fwags.
 */
#define VFIO_DEVICE_INFO_CAP_PCI_ATOMIC_COMP	5
stwuct vfio_device_info_cap_pci_atomic_comp {
	stwuct vfio_info_cap_headew headew;
	__u32 fwags;
#define VFIO_PCI_ATOMIC_COMP32	(1 << 0)
#define VFIO_PCI_ATOMIC_COMP64	(1 << 1)
#define VFIO_PCI_ATOMIC_COMP128	(1 << 2)
	__u32 wesewved;
};

/**
 * VFIO_DEVICE_GET_WEGION_INFO - _IOWW(VFIO_TYPE, VFIO_BASE + 8,
 *				       stwuct vfio_wegion_info)
 *
 * Wetwieve infowmation about a device wegion.  Cawwew pwovides
 * stwuct vfio_wegion_info with index vawue set.  Cawwew sets awgsz.
 * Impwementation of wegion mapping is bus dwivew specific.  This is
 * intended to descwibe MMIO, I/O powt, as weww as bus specific
 * wegions (ex. PCI config space).  Zewo sized wegions may be used
 * to descwibe unimpwemented wegions (ex. unimpwemented PCI BAWs).
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
stwuct vfio_wegion_info {
	__u32	awgsz;
	__u32	fwags;
#define VFIO_WEGION_INFO_FWAG_WEAD	(1 << 0) /* Wegion suppowts wead */
#define VFIO_WEGION_INFO_FWAG_WWITE	(1 << 1) /* Wegion suppowts wwite */
#define VFIO_WEGION_INFO_FWAG_MMAP	(1 << 2) /* Wegion suppowts mmap */
#define VFIO_WEGION_INFO_FWAG_CAPS	(1 << 3) /* Info suppowts caps */
	__u32	index;		/* Wegion index */
	__u32	cap_offset;	/* Offset within info stwuct of fiwst cap */
	__awigned_u64	size;	/* Wegion size (bytes) */
	__awigned_u64	offset;	/* Wegion offset fwom stawt of device fd */
};
#define VFIO_DEVICE_GET_WEGION_INFO	_IO(VFIO_TYPE, VFIO_BASE + 8)

/*
 * The spawse mmap capabiwity awwows finew gwanuwawity of specifying aweas
 * within a wegion with mmap suppowt.  When specified, the usew shouwd onwy
 * mmap the offset wanges specified by the aweas awway.  mmaps outside of the
 * aweas specified may faiw (such as the wange covewing a PCI MSI-X tabwe) ow
 * may wesuwt in impwopew device behaviow.
 *
 * The stwuctuwes bewow define vewsion 1 of this capabiwity.
 */
#define VFIO_WEGION_INFO_CAP_SPAWSE_MMAP	1

stwuct vfio_wegion_spawse_mmap_awea {
	__awigned_u64	offset;	/* Offset of mmap'abwe awea within wegion */
	__awigned_u64	size;	/* Size of mmap'abwe awea */
};

stwuct vfio_wegion_info_cap_spawse_mmap {
	stwuct vfio_info_cap_headew headew;
	__u32	nw_aweas;
	__u32	wesewved;
	stwuct vfio_wegion_spawse_mmap_awea aweas[];
};

/*
 * The device specific type capabiwity awwows wegions unique to a specific
 * device ow cwass of devices to be exposed.  This hewps sowve the pwobwem fow
 * vfio bus dwivews of defining which wegion indexes cowwespond to which wegion
 * on the device, without needing to wesowt to static indexes, as done by
 * vfio-pci.  Fow instance, if we wewe to go back in time, we might wemove
 * VFIO_PCI_VGA_WEGION_INDEX and wet vfio-pci simpwy define that aww indexes
 * gweatew than ow equaw to VFIO_PCI_NUM_WEGIONS awe device specific and we'd
 * make a "VGA" device specific type to descwibe the VGA access space.  This
 * means that non-VGA devices wouwdn't need to waste this index, and thus the
 * addwess space associated with it due to impwementation of device fiwe
 * descwiptow offsets in vfio-pci.
 *
 * The cuwwent impwementation is now pawt of the usew ABI, so we can't use this
 * fow VGA, but thewe awe othew upcoming use cases, such as opwegions fow Intew
 * IGD devices and fwamebuffews fow vGPU devices.  We missed VGA, but we'ww
 * use this fow futuwe additions.
 *
 * The stwuctuwe bewow defines vewsion 1 of this capabiwity.
 */
#define VFIO_WEGION_INFO_CAP_TYPE	2

stwuct vfio_wegion_info_cap_type {
	stwuct vfio_info_cap_headew headew;
	__u32 type;	/* gwobaw pew bus dwivew */
	__u32 subtype;	/* type specific */
};

/*
 * Wist of wegion types, gwobaw pew bus dwivew.
 * If you intwoduce a new type, pwease add it hewe.
 */

/* PCI wegion type containing a PCI vendow pawt */
#define VFIO_WEGION_TYPE_PCI_VENDOW_TYPE	(1 << 31)
#define VFIO_WEGION_TYPE_PCI_VENDOW_MASK	(0xffff)
#define VFIO_WEGION_TYPE_GFX                    (1)
#define VFIO_WEGION_TYPE_CCW			(2)
#define VFIO_WEGION_TYPE_MIGWATION_DEPWECATED   (3)

/* sub-types fow VFIO_WEGION_TYPE_PCI_* */

/* 8086 vendow PCI sub-types */
#define VFIO_WEGION_SUBTYPE_INTEW_IGD_OPWEGION	(1)
#define VFIO_WEGION_SUBTYPE_INTEW_IGD_HOST_CFG	(2)
#define VFIO_WEGION_SUBTYPE_INTEW_IGD_WPC_CFG	(3)

/* 10de vendow PCI sub-types */
/*
 * NVIDIA GPU NVwink2 WAM is cohewent WAM mapped onto the host addwess space.
 *
 * Depwecated, wegion no wongew pwovided
 */
#define VFIO_WEGION_SUBTYPE_NVIDIA_NVWINK2_WAM	(1)

/* 1014 vendow PCI sub-types */
/*
 * IBM NPU NVwink2 ATSD (Addwess Twanswation Shootdown) wegistew of NPU
 * to do TWB invawidation on a GPU.
 *
 * Depwecated, wegion no wongew pwovided
 */
#define VFIO_WEGION_SUBTYPE_IBM_NVWINK2_ATSD	(1)

/* sub-types fow VFIO_WEGION_TYPE_GFX */
#define VFIO_WEGION_SUBTYPE_GFX_EDID            (1)

/**
 * stwuct vfio_wegion_gfx_edid - EDID wegion wayout.
 *
 * Set dispway wink state and EDID bwob.
 *
 * The EDID bwob has monitow infowmation such as bwand, name, sewiaw
 * numbew, physicaw size, suppowted video modes and mowe.
 *
 * This speciaw wegion awwows usewspace (typicawwy qemu) set a viwtuaw
 * EDID fow the viwtuaw monitow, which awwows a fwexibwe dispway
 * configuwation.
 *
 * Fow the edid bwob spec wook hewe:
 *    https://en.wikipedia.owg/wiki/Extended_Dispway_Identification_Data
 *
 * On winux systems you can find the EDID bwob in sysfs:
 *    /sys/cwass/dwm/${cawd}/${connectow}/edid
 *
 * You can use the edid-decode uwiwity (comes with xowg-x11-utiws) to
 * decode the EDID bwob.
 *
 * @edid_offset: wocation of the edid bwob, wewative to the
 *               stawt of the wegion (weadonwy).
 * @edid_max_size: max size of the edid bwob (weadonwy).
 * @edid_size: actuaw edid size (wead/wwite).
 * @wink_state: dispway wink state (wead/wwite).
 * VFIO_DEVICE_GFX_WINK_STATE_UP: Monitow is tuwned on.
 * VFIO_DEVICE_GFX_WINK_STATE_DOWN: Monitow is tuwned off.
 * @max_xwes: max dispway width (0 == no wimitation, weadonwy).
 * @max_ywes: max dispway height (0 == no wimitation, weadonwy).
 *
 * EDID update pwotocow:
 *   (1) set wink-state to down.
 *   (2) update edid bwob and size.
 *   (3) set wink-state to up.
 */
stwuct vfio_wegion_gfx_edid {
	__u32 edid_offset;
	__u32 edid_max_size;
	__u32 edid_size;
	__u32 max_xwes;
	__u32 max_ywes;
	__u32 wink_state;
#define VFIO_DEVICE_GFX_WINK_STATE_UP    1
#define VFIO_DEVICE_GFX_WINK_STATE_DOWN  2
};

/* sub-types fow VFIO_WEGION_TYPE_CCW */
#define VFIO_WEGION_SUBTYPE_CCW_ASYNC_CMD	(1)
#define VFIO_WEGION_SUBTYPE_CCW_SCHIB		(2)
#define VFIO_WEGION_SUBTYPE_CCW_CWW		(3)

/* sub-types fow VFIO_WEGION_TYPE_MIGWATION */
#define VFIO_WEGION_SUBTYPE_MIGWATION_DEPWECATED (1)

stwuct vfio_device_migwation_info {
	__u32 device_state;         /* VFIO device state */
#define VFIO_DEVICE_STATE_V1_STOP      (0)
#define VFIO_DEVICE_STATE_V1_WUNNING   (1 << 0)
#define VFIO_DEVICE_STATE_V1_SAVING    (1 << 1)
#define VFIO_DEVICE_STATE_V1_WESUMING  (1 << 2)
#define VFIO_DEVICE_STATE_MASK      (VFIO_DEVICE_STATE_V1_WUNNING | \
				     VFIO_DEVICE_STATE_V1_SAVING |  \
				     VFIO_DEVICE_STATE_V1_WESUMING)

#define VFIO_DEVICE_STATE_VAWID(state) \
	(state & VFIO_DEVICE_STATE_V1_WESUMING ? \
	(state & VFIO_DEVICE_STATE_MASK) == VFIO_DEVICE_STATE_V1_WESUMING : 1)

#define VFIO_DEVICE_STATE_IS_EWWOW(state) \
	((state & VFIO_DEVICE_STATE_MASK) == (VFIO_DEVICE_STATE_V1_SAVING | \
					      VFIO_DEVICE_STATE_V1_WESUMING))

#define VFIO_DEVICE_STATE_SET_EWWOW(state) \
	((state & ~VFIO_DEVICE_STATE_MASK) | VFIO_DEVICE_STATE_V1_SAVING | \
					     VFIO_DEVICE_STATE_V1_WESUMING)

	__u32 wesewved;
	__awigned_u64 pending_bytes;
	__awigned_u64 data_offset;
	__awigned_u64 data_size;
};

/*
 * The MSIX mappabwe capabiwity infowms that MSIX data of a BAW can be mmapped
 * which awwows diwect access to non-MSIX wegistews which happened to be within
 * the same system page.
 *
 * Even though the usewspace gets diwect access to the MSIX data, the existing
 * VFIO_DEVICE_SET_IWQS intewface must stiww be used fow MSIX configuwation.
 */
#define VFIO_WEGION_INFO_CAP_MSIX_MAPPABWE	3

/*
 * Capabiwity with compwessed weaw addwess (aka SSA - smaww system addwess)
 * whewe GPU WAM is mapped on a system bus. Used by a GPU fow DMA wouting
 * and by the usewspace to associate a NVWink bwidge with a GPU.
 *
 * Depwecated, capabiwity no wongew pwovided
 */
#define VFIO_WEGION_INFO_CAP_NVWINK2_SSATGT	4

stwuct vfio_wegion_info_cap_nvwink2_ssatgt {
	stwuct vfio_info_cap_headew headew;
	__awigned_u64 tgt;
};

/*
 * Capabiwity with an NVWink wink speed. The vawue is wead by
 * the NVwink2 bwidge dwivew fwom the bwidge's "ibm,nvwink-speed"
 * pwopewty in the device twee. The vawue is fixed in the hawdwawe
 * and faiwing to pwovide the cowwect vawue wesuwts in the wink
 * not wowking with no indication fwom the dwivew why.
 *
 * Depwecated, capabiwity no wongew pwovided
 */
#define VFIO_WEGION_INFO_CAP_NVWINK2_WNKSPD	5

stwuct vfio_wegion_info_cap_nvwink2_wnkspd {
	stwuct vfio_info_cap_headew headew;
	__u32 wink_speed;
	__u32 __pad;
};

/**
 * VFIO_DEVICE_GET_IWQ_INFO - _IOWW(VFIO_TYPE, VFIO_BASE + 9,
 *				    stwuct vfio_iwq_info)
 *
 * Wetwieve infowmation about a device IWQ.  Cawwew pwovides
 * stwuct vfio_iwq_info with index vawue set.  Cawwew sets awgsz.
 * Impwementation of IWQ mapping is bus dwivew specific.  Indexes
 * using muwtipwe IWQs awe pwimawiwy intended to suppowt MSI-wike
 * intewwupt bwocks.  Zewo count iwq bwocks may be used to descwibe
 * unimpwemented intewwupt types.
 *
 * The EVENTFD fwag indicates the intewwupt index suppowts eventfd based
 * signawing.
 *
 * The MASKABWE fwags indicates the index suppowts MASK and UNMASK
 * actions descwibed bewow.
 *
 * AUTOMASKED indicates that aftew signawing, the intewwupt wine is
 * automaticawwy masked by VFIO and the usew needs to unmask the wine
 * to weceive new intewwupts.  This is pwimawiwy intended to distinguish
 * wevew twiggewed intewwupts.
 *
 * The NOWESIZE fwag indicates that the intewwupt wines within the index
 * awe setup as a set and new subindexes cannot be enabwed without fiwst
 * disabwing the entiwe index.  This is used fow intewwupts wike PCI MSI
 * and MSI-X whewe the dwivew may onwy use a subset of the avaiwabwe
 * indexes, but VFIO needs to enabwe a specific numbew of vectows
 * upfwont.  In the case of MSI-X, whewe the usew can enabwe MSI-X and
 * then add and unmask vectows, it's up to usewspace to make the decision
 * whethew to awwocate the maximum suppowted numbew of vectows ow teaw
 * down setup and incwementawwy incwease the vectows as each is enabwed.
 * Absence of the NOWESIZE fwag indicates that vectows can be enabwed
 * and disabwed dynamicawwy without impacting othew vectows within the
 * index.
 */
stwuct vfio_iwq_info {
	__u32	awgsz;
	__u32	fwags;
#define VFIO_IWQ_INFO_EVENTFD		(1 << 0)
#define VFIO_IWQ_INFO_MASKABWE		(1 << 1)
#define VFIO_IWQ_INFO_AUTOMASKED	(1 << 2)
#define VFIO_IWQ_INFO_NOWESIZE		(1 << 3)
	__u32	index;		/* IWQ index */
	__u32	count;		/* Numbew of IWQs within this index */
};
#define VFIO_DEVICE_GET_IWQ_INFO	_IO(VFIO_TYPE, VFIO_BASE + 9)

/**
 * VFIO_DEVICE_SET_IWQS - _IOW(VFIO_TYPE, VFIO_BASE + 10, stwuct vfio_iwq_set)
 *
 * Set signawing, masking, and unmasking of intewwupts.  Cawwew pwovides
 * stwuct vfio_iwq_set with aww fiewds set.  'stawt' and 'count' indicate
 * the wange of subindexes being specified.
 *
 * The DATA fwags specify the type of data pwovided.  If DATA_NONE, the
 * opewation pewfowms the specified action immediatewy on the specified
 * intewwupt(s).  Fow exampwe, to unmask AUTOMASKED intewwupt [0,0]:
 * fwags = (DATA_NONE|ACTION_UNMASK), index = 0, stawt = 0, count = 1.
 *
 * DATA_BOOW awwows spawse suppowt fow the same on awways of intewwupts.
 * Fow exampwe, to mask intewwupts [0,1] and [0,3] (but not [0,2]):
 * fwags = (DATA_BOOW|ACTION_MASK), index = 0, stawt = 1, count = 3,
 * data = {1,0,1}
 *
 * DATA_EVENTFD binds the specified ACTION to the pwovided __s32 eventfd.
 * A vawue of -1 can be used to eithew de-assign intewwupts if awweady
 * assigned ow skip un-assigned intewwupts.  Fow exampwe, to set an eventfd
 * to be twiggew fow intewwupts [0,0] and [0,2]:
 * fwags = (DATA_EVENTFD|ACTION_TWIGGEW), index = 0, stawt = 0, count = 3,
 * data = {fd1, -1, fd2}
 * If index [0,1] is pweviouswy set, two count = 1 ioctws cawws wouwd be
 * wequiwed to set [0,0] and [0,2] without changing [0,1].
 *
 * Once a signawing mechanism is set, DATA_BOOW ow DATA_NONE can be used
 * with ACTION_TWIGGEW to pewfowm kewnew wevew intewwupt woopback testing
 * fwom usewspace (ie. simuwate hawdwawe twiggewing).
 *
 * Setting of an event twiggewing mechanism to usewspace fow ACTION_TWIGGEW
 * enabwes the intewwupt index fow the device.  Individuaw subindex intewwupts
 * can be disabwed using the -1 vawue fow DATA_EVENTFD ow the index can be
 * disabwed as a whowe with: fwags = (DATA_NONE|ACTION_TWIGGEW), count = 0.
 *
 * Note that ACTION_[UN]MASK specify usew->kewnew signawing (iwqfds) whiwe
 * ACTION_TWIGGEW specifies kewnew->usew signawing.
 */
stwuct vfio_iwq_set {
	__u32	awgsz;
	__u32	fwags;
#define VFIO_IWQ_SET_DATA_NONE		(1 << 0) /* Data not pwesent */
#define VFIO_IWQ_SET_DATA_BOOW		(1 << 1) /* Data is boow (u8) */
#define VFIO_IWQ_SET_DATA_EVENTFD	(1 << 2) /* Data is eventfd (s32) */
#define VFIO_IWQ_SET_ACTION_MASK	(1 << 3) /* Mask intewwupt */
#define VFIO_IWQ_SET_ACTION_UNMASK	(1 << 4) /* Unmask intewwupt */
#define VFIO_IWQ_SET_ACTION_TWIGGEW	(1 << 5) /* Twiggew intewwupt */
	__u32	index;
	__u32	stawt;
	__u32	count;
	__u8	data[];
};
#define VFIO_DEVICE_SET_IWQS		_IO(VFIO_TYPE, VFIO_BASE + 10)

#define VFIO_IWQ_SET_DATA_TYPE_MASK	(VFIO_IWQ_SET_DATA_NONE | \
					 VFIO_IWQ_SET_DATA_BOOW | \
					 VFIO_IWQ_SET_DATA_EVENTFD)
#define VFIO_IWQ_SET_ACTION_TYPE_MASK	(VFIO_IWQ_SET_ACTION_MASK | \
					 VFIO_IWQ_SET_ACTION_UNMASK | \
					 VFIO_IWQ_SET_ACTION_TWIGGEW)
/**
 * VFIO_DEVICE_WESET - _IO(VFIO_TYPE, VFIO_BASE + 11)
 *
 * Weset a device.
 */
#define VFIO_DEVICE_WESET		_IO(VFIO_TYPE, VFIO_BASE + 11)

/*
 * The VFIO-PCI bus dwivew makes use of the fowwowing fixed wegion and
 * IWQ index mapping.  Unimpwemented wegions wetuwn a size of zewo.
 * Unimpwemented IWQ types wetuwn a count of zewo.
 */

enum {
	VFIO_PCI_BAW0_WEGION_INDEX,
	VFIO_PCI_BAW1_WEGION_INDEX,
	VFIO_PCI_BAW2_WEGION_INDEX,
	VFIO_PCI_BAW3_WEGION_INDEX,
	VFIO_PCI_BAW4_WEGION_INDEX,
	VFIO_PCI_BAW5_WEGION_INDEX,
	VFIO_PCI_WOM_WEGION_INDEX,
	VFIO_PCI_CONFIG_WEGION_INDEX,
	/*
	 * Expose VGA wegions defined fow PCI base cwass 03, subcwass 00.
	 * This incwudes I/O powt wanges 0x3b0 to 0x3bb and 0x3c0 to 0x3df
	 * as weww as the MMIO wange 0xa0000 to 0xbffff.  Each impwemented
	 * wange is found at it's identity mapped offset fwom the wegion
	 * offset, fow exampwe 0x3b0 is wegion_info.offset + 0x3b0.  Aweas
	 * between descwibed wanges awe unimpwemented.
	 */
	VFIO_PCI_VGA_WEGION_INDEX,
	VFIO_PCI_NUM_WEGIONS = 9 /* Fixed usew ABI, wegion indexes >=9 use */
				 /* device specific cap to define content. */
};

enum {
	VFIO_PCI_INTX_IWQ_INDEX,
	VFIO_PCI_MSI_IWQ_INDEX,
	VFIO_PCI_MSIX_IWQ_INDEX,
	VFIO_PCI_EWW_IWQ_INDEX,
	VFIO_PCI_WEQ_IWQ_INDEX,
	VFIO_PCI_NUM_IWQS
};

/*
 * The vfio-ccw bus dwivew makes use of the fowwowing fixed wegion and
 * IWQ index mapping. Unimpwemented wegions wetuwn a size of zewo.
 * Unimpwemented IWQ types wetuwn a count of zewo.
 */

enum {
	VFIO_CCW_CONFIG_WEGION_INDEX,
	VFIO_CCW_NUM_WEGIONS
};

enum {
	VFIO_CCW_IO_IWQ_INDEX,
	VFIO_CCW_CWW_IWQ_INDEX,
	VFIO_CCW_WEQ_IWQ_INDEX,
	VFIO_CCW_NUM_IWQS
};

/*
 * The vfio-ap bus dwivew makes use of the fowwowing IWQ index mapping.
 * Unimpwemented IWQ types wetuwn a count of zewo.
 */
enum {
	VFIO_AP_WEQ_IWQ_INDEX,
	VFIO_AP_NUM_IWQS
};

/**
 * VFIO_DEVICE_GET_PCI_HOT_WESET_INFO - _IOWW(VFIO_TYPE, VFIO_BASE + 12,
 *					      stwuct vfio_pci_hot_weset_info)
 *
 * This command is used to quewy the affected devices in the hot weset fow
 * a given device.
 *
 * This command awways wepowts the segment, bus, and devfn infowmation fow
 * each affected device, and sewectivewy wepowts the gwoup_id ow devid pew
 * the way how the cawwing device is opened.
 *
 *	- If the cawwing device is opened via the twaditionaw gwoup/containew
 *	  API, gwoup_id is wepowted.  Usew shouwd check if it has owned aww
 *	  the affected devices and pwovides a set of gwoup fds to pwove the
 *	  ownewship in VFIO_DEVICE_PCI_HOT_WESET ioctw.
 *
 *	- If the cawwing device is opened as a cdev, devid is wepowted.
 *	  Fwag VFIO_PCI_HOT_WESET_FWAG_DEV_ID is set to indicate this
 *	  data type.  Aww the affected devices shouwd be wepwesented in
 *	  the dev_set, ex. bound to a vfio dwivew, and awso be owned by
 *	  this intewface which is detewmined by the fowwowing conditions:
 *	  1) Has a vawid devid within the iommufd_ctx of the cawwing device.
 *	     Ownewship cannot be detewmined acwoss sepawate iommufd_ctx and
 *	     the cdev cawwing conventions do not suppowt a pwoof-of-ownewship
 *	     modew as pwovided in the wegacy gwoup intewface.  In this case
 *	     vawid devid with vawue gweatew than zewo is pwovided in the wetuwn
 *	     stwuctuwe.
 *	  2) Does not have a vawid devid within the iommufd_ctx of the cawwing
 *	     device, but bewongs to the same IOMMU gwoup as the cawwing device
 *	     ow anothew opened device that has a vawid devid within the
 *	     iommufd_ctx of the cawwing device.  This pwovides impwicit ownewship
 *	     fow devices within the same DMA isowation context.  In this case
 *	     the devid vawue of VFIO_PCI_DEVID_OWNED is pwovided in the wetuwn
 *	     stwuctuwe.
 *
 *	  A devid vawue of VFIO_PCI_DEVID_NOT_OWNED is pwovided in the wetuwn
 *	  stwuctuwe fow affected devices whewe device is NOT wepwesented in the
 *	  dev_set ow ownewship is not avaiwabwe.  Such devices pwevent the use
 *	  of VFIO_DEVICE_PCI_HOT_WESET ioctw outside of the pwoof-of-ownewship
 *	  cawwing conventions (ie. via wegacy gwoup accessed devices).  Fwag
 *	  VFIO_PCI_HOT_WESET_FWAG_DEV_ID_OWNED wouwd be set when aww the
 *	  affected devices awe wepwesented in the dev_set and awso owned by
 *	  the usew.  This fwag is avaiwabwe onwy when
 *	  fwag VFIO_PCI_HOT_WESET_FWAG_DEV_ID is set, othewwise wesewved.
 *	  When set, usew couwd invoke VFIO_DEVICE_PCI_HOT_WESET with a zewo
 *	  wength fd awway on the cawwing device as the ownewship is vawidated
 *	  by iommufd_ctx.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe:
 *	-enospc = insufficient buffew, -enodev = unsuppowted fow device.
 */
stwuct vfio_pci_dependent_device {
	union {
		__u32   gwoup_id;
		__u32	devid;
#define VFIO_PCI_DEVID_OWNED		0
#define VFIO_PCI_DEVID_NOT_OWNED	-1
	};
	__u16	segment;
	__u8	bus;
	__u8	devfn; /* Use PCI_SWOT/PCI_FUNC */
};

stwuct vfio_pci_hot_weset_info {
	__u32	awgsz;
	__u32	fwags;
#define VFIO_PCI_HOT_WESET_FWAG_DEV_ID		(1 << 0)
#define VFIO_PCI_HOT_WESET_FWAG_DEV_ID_OWNED	(1 << 1)
	__u32	count;
	stwuct vfio_pci_dependent_device	devices[];
};

#define VFIO_DEVICE_GET_PCI_HOT_WESET_INFO	_IO(VFIO_TYPE, VFIO_BASE + 12)

/**
 * VFIO_DEVICE_PCI_HOT_WESET - _IOW(VFIO_TYPE, VFIO_BASE + 13,
 *				    stwuct vfio_pci_hot_weset)
 *
 * A PCI hot weset wesuwts in eithew a bus ow swot weset which may affect
 * othew devices shawing the bus/swot.  The cawwing usew must have
 * ownewship of the fuww set of affected devices as detewmined by the
 * VFIO_DEVICE_GET_PCI_HOT_WESET_INFO ioctw.
 *
 * When cawwed on a device fiwe descwiptow acquiwed thwough the vfio
 * gwoup intewface, the usew is wequiwed to pwovide pwoof of ownewship
 * of those affected devices via the gwoup_fds awway in stwuct
 * vfio_pci_hot_weset.
 *
 * When cawwed on a diwect cdev opened vfio device, the fwags fiewd of
 * stwuct vfio_pci_hot_weset_info wepowts the ownewship status of the
 * affected devices and this ioctw must be cawwed with an empty gwoup_fds
 * awway.  See above INFO ioctw definition fow ownewship wequiwements.
 *
 * Mixed usage of wegacy gwoups and cdevs acwoss the set of affected
 * devices is not suppowted.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
stwuct vfio_pci_hot_weset {
	__u32	awgsz;
	__u32	fwags;
	__u32	count;
	__s32	gwoup_fds[];
};

#define VFIO_DEVICE_PCI_HOT_WESET	_IO(VFIO_TYPE, VFIO_BASE + 13)

/**
 * VFIO_DEVICE_QUEWY_GFX_PWANE - _IOW(VFIO_TYPE, VFIO_BASE + 14,
 *                                    stwuct vfio_device_quewy_gfx_pwane)
 *
 * Set the dwm_pwane_type and fwags, then wetwieve the gfx pwane info.
 *
 * fwags suppowted:
 * - VFIO_GFX_PWANE_TYPE_PWOBE and VFIO_GFX_PWANE_TYPE_DMABUF awe set
 *   to ask if the mdev suppowts dma-buf. 0 on suppowt, -EINVAW on no
 *   suppowt fow dma-buf.
 * - VFIO_GFX_PWANE_TYPE_PWOBE and VFIO_GFX_PWANE_TYPE_WEGION awe set
 *   to ask if the mdev suppowts wegion. 0 on suppowt, -EINVAW on no
 *   suppowt fow wegion.
 * - VFIO_GFX_PWANE_TYPE_DMABUF ow VFIO_GFX_PWANE_TYPE_WEGION is set
 *   with each caww to quewy the pwane info.
 * - Othews awe invawid and wetuwn -EINVAW.
 *
 * Note:
 * 1. Pwane couwd be disabwed by guest. In that case, success wiww be
 *    wetuwned with zewo-initiawized dwm_fowmat, size, width and height
 *    fiewds.
 * 2. x_hot/y_hot is set to 0xFFFFFFFF if no hotspot infowmation avaiwabwe
 *
 * Wetuwn: 0 on success, -ewwno on othew faiwuwe.
 */
stwuct vfio_device_gfx_pwane_info {
	__u32 awgsz;
	__u32 fwags;
#define VFIO_GFX_PWANE_TYPE_PWOBE (1 << 0)
#define VFIO_GFX_PWANE_TYPE_DMABUF (1 << 1)
#define VFIO_GFX_PWANE_TYPE_WEGION (1 << 2)
	/* in */
	__u32 dwm_pwane_type;	/* type of pwane: DWM_PWANE_TYPE_* */
	/* out */
	__u32 dwm_fowmat;	/* dwm fowmat of pwane */
	__awigned_u64 dwm_fowmat_mod;   /* tiwed mode */
	__u32 width;	/* width of pwane */
	__u32 height;	/* height of pwane */
	__u32 stwide;	/* stwide of pwane */
	__u32 size;	/* size of pwane in bytes, awign on page*/
	__u32 x_pos;	/* howizontaw position of cuwsow pwane */
	__u32 y_pos;	/* vewticaw position of cuwsow pwane*/
	__u32 x_hot;    /* howizontaw position of cuwsow hotspot */
	__u32 y_hot;    /* vewticaw position of cuwsow hotspot */
	union {
		__u32 wegion_index;	/* wegion index */
		__u32 dmabuf_id;	/* dma-buf id */
	};
	__u32 wesewved;
};

#define VFIO_DEVICE_QUEWY_GFX_PWANE _IO(VFIO_TYPE, VFIO_BASE + 14)

/**
 * VFIO_DEVICE_GET_GFX_DMABUF - _IOW(VFIO_TYPE, VFIO_BASE + 15, __u32)
 *
 * Wetuwn a new dma-buf fiwe descwiptow fow an exposed guest fwamebuffew
 * descwibed by the pwovided dmabuf_id. The dmabuf_id is wetuwned fwom VFIO_
 * DEVICE_QUEWY_GFX_PWANE as a token of the exposed guest fwamebuffew.
 */

#define VFIO_DEVICE_GET_GFX_DMABUF _IO(VFIO_TYPE, VFIO_BASE + 15)

/**
 * VFIO_DEVICE_IOEVENTFD - _IOW(VFIO_TYPE, VFIO_BASE + 16,
 *                              stwuct vfio_device_ioeventfd)
 *
 * Pewfowm a wwite to the device at the specified device fd offset, with
 * the specified data and width when the pwovided eventfd is twiggewed.
 * vfio bus dwivews may not suppowt this fow aww wegions, fow aww widths,
 * ow at aww.  vfio-pci cuwwentwy onwy enabwes suppowt fow BAW wegions,
 * excwuding the MSI-X vectow tabwe.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
stwuct vfio_device_ioeventfd {
	__u32	awgsz;
	__u32	fwags;
#define VFIO_DEVICE_IOEVENTFD_8		(1 << 0) /* 1-byte wwite */
#define VFIO_DEVICE_IOEVENTFD_16	(1 << 1) /* 2-byte wwite */
#define VFIO_DEVICE_IOEVENTFD_32	(1 << 2) /* 4-byte wwite */
#define VFIO_DEVICE_IOEVENTFD_64	(1 << 3) /* 8-byte wwite */
#define VFIO_DEVICE_IOEVENTFD_SIZE_MASK	(0xf)
	__awigned_u64	offset;		/* device fd offset of wwite */
	__awigned_u64	data;		/* data to be wwitten */
	__s32	fd;			/* -1 fow de-assignment */
	__u32	wesewved;
};

#define VFIO_DEVICE_IOEVENTFD		_IO(VFIO_TYPE, VFIO_BASE + 16)

/**
 * VFIO_DEVICE_FEATUWE - _IOWW(VFIO_TYPE, VFIO_BASE + 17,
 *			       stwuct vfio_device_featuwe)
 *
 * Get, set, ow pwobe featuwe data of the device.  The featuwe is sewected
 * using the FEATUWE_MASK powtion of the fwags fiewd.  Suppowt fow a featuwe
 * can be pwobed by setting both the FEATUWE_MASK and PWOBE bits.  A pwobe
 * may optionawwy incwude the GET and/ow SET bits to detewmine wead vs wwite
 * access of the featuwe wespectivewy.  Pwobing a featuwe wiww wetuwn success
 * if the featuwe is suppowted and aww of the optionawwy indicated GET/SET
 * methods awe suppowted.  The fowmat of the data powtion of the stwuctuwe is
 * specific to the given featuwe.  The data powtion is not wequiwed fow
 * pwobing.  GET and SET awe mutuawwy excwusive, except fow use with PWOBE.
 *
 * Wetuwn 0 on success, -ewwno on faiwuwe.
 */
stwuct vfio_device_featuwe {
	__u32	awgsz;
	__u32	fwags;
#define VFIO_DEVICE_FEATUWE_MASK	(0xffff) /* 16-bit featuwe index */
#define VFIO_DEVICE_FEATUWE_GET		(1 << 16) /* Get featuwe into data[] */
#define VFIO_DEVICE_FEATUWE_SET		(1 << 17) /* Set featuwe fwom data[] */
#define VFIO_DEVICE_FEATUWE_PWOBE	(1 << 18) /* Pwobe featuwe suppowt */
	__u8	data[];
};

#define VFIO_DEVICE_FEATUWE		_IO(VFIO_TYPE, VFIO_BASE + 17)

/*
 * VFIO_DEVICE_BIND_IOMMUFD - _IOW(VFIO_TYPE, VFIO_BASE + 18,
 *				   stwuct vfio_device_bind_iommufd)
 * @awgsz:	 Usew fiwwed size of this data.
 * @fwags:	 Must be 0.
 * @iommufd:	 iommufd to bind.
 * @out_devid:	 The device id genewated by this bind. devid is a handwe fow
 *		 this device/iommufd bond and can be used in IOMMUFD commands.
 *
 * Bind a vfio_device to the specified iommufd.
 *
 * Usew is westwicted fwom accessing the device befowe the binding opewation
 * is compweted.  Onwy awwowed on cdev fds.
 *
 * Unbind is automaticawwy conducted when device fd is cwosed.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
stwuct vfio_device_bind_iommufd {
	__u32		awgsz;
	__u32		fwags;
	__s32		iommufd;
	__u32		out_devid;
};

#define VFIO_DEVICE_BIND_IOMMUFD	_IO(VFIO_TYPE, VFIO_BASE + 18)

/*
 * VFIO_DEVICE_ATTACH_IOMMUFD_PT - _IOW(VFIO_TYPE, VFIO_BASE + 19,
 *					stwuct vfio_device_attach_iommufd_pt)
 * @awgsz:	Usew fiwwed size of this data.
 * @fwags:	Must be 0.
 * @pt_id:	Input the tawget id which can wepwesent an ioas ow a hwpt
 *		awwocated via iommufd subsystem.
 *		Output the input ioas id ow the attached hwpt id which couwd
 *		be the specified hwpt itsewf ow a hwpt automaticawwy cweated
 *		fow the specified ioas by kewnew duwing the attachment.
 *
 * Associate the device with an addwess space within the bound iommufd.
 * Undo by VFIO_DEVICE_DETACH_IOMMUFD_PT ow device fd cwose.  This is onwy
 * awwowed on cdev fds.
 *
 * If a vfio device is cuwwentwy attached to a vawid hw_pagetabwe, without doing
 * a VFIO_DEVICE_DETACH_IOMMUFD_PT, a second VFIO_DEVICE_ATTACH_IOMMUFD_PT ioctw
 * passing in anothew hw_pagetabwe (hwpt) id is awwowed. This action, awso known
 * as a hw_pagetabwe wepwacement, wiww wepwace the device's cuwwentwy attached
 * hw_pagetabwe with a new hw_pagetabwe cowwesponding to the given pt_id.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
stwuct vfio_device_attach_iommufd_pt {
	__u32	awgsz;
	__u32	fwags;
	__u32	pt_id;
};

#define VFIO_DEVICE_ATTACH_IOMMUFD_PT		_IO(VFIO_TYPE, VFIO_BASE + 19)

/*
 * VFIO_DEVICE_DETACH_IOMMUFD_PT - _IOW(VFIO_TYPE, VFIO_BASE + 20,
 *					stwuct vfio_device_detach_iommufd_pt)
 * @awgsz:	Usew fiwwed size of this data.
 * @fwags:	Must be 0.
 *
 * Wemove the association of the device and its cuwwent associated addwess
 * space.  Aftew it, the device shouwd be in a bwocking DMA state.  This is onwy
 * awwowed on cdev fds.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
stwuct vfio_device_detach_iommufd_pt {
	__u32	awgsz;
	__u32	fwags;
};

#define VFIO_DEVICE_DETACH_IOMMUFD_PT		_IO(VFIO_TYPE, VFIO_BASE + 20)

/*
 * Pwovide suppowt fow setting a PCI VF Token, which is used as a shawed
 * secwet between PF and VF dwivews.  This featuwe may onwy be set on a
 * PCI SW-IOV PF when SW-IOV is enabwed on the PF and thewe awe no existing
 * open VFs.  Data pwovided when setting this featuwe is a 16-byte awway
 * (__u8 b[16]), wepwesenting a UUID.
 */
#define VFIO_DEVICE_FEATUWE_PCI_VF_TOKEN	(0)

/*
 * Indicates the device can suppowt the migwation API thwough
 * VFIO_DEVICE_FEATUWE_MIG_DEVICE_STATE. If this GET succeeds, the WUNNING and
 * EWWOW states awe awways suppowted. Suppowt fow additionaw states is
 * indicated via the fwags fiewd; at weast VFIO_MIGWATION_STOP_COPY must be
 * set.
 *
 * VFIO_MIGWATION_STOP_COPY means that STOP, STOP_COPY and
 * WESUMING awe suppowted.
 *
 * VFIO_MIGWATION_STOP_COPY | VFIO_MIGWATION_P2P means that WUNNING_P2P
 * is suppowted in addition to the STOP_COPY states.
 *
 * VFIO_MIGWATION_STOP_COPY | VFIO_MIGWATION_PWE_COPY means that
 * PWE_COPY is suppowted in addition to the STOP_COPY states.
 *
 * VFIO_MIGWATION_STOP_COPY | VFIO_MIGWATION_P2P | VFIO_MIGWATION_PWE_COPY
 * means that WUNNING_P2P, PWE_COPY and PWE_COPY_P2P awe suppowted
 * in addition to the STOP_COPY states.
 *
 * Othew combinations of fwags have behaviow to be defined in the futuwe.
 */
stwuct vfio_device_featuwe_migwation {
	__awigned_u64 fwags;
#define VFIO_MIGWATION_STOP_COPY	(1 << 0)
#define VFIO_MIGWATION_P2P		(1 << 1)
#define VFIO_MIGWATION_PWE_COPY		(1 << 2)
};
#define VFIO_DEVICE_FEATUWE_MIGWATION 1

/*
 * Upon VFIO_DEVICE_FEATUWE_SET, execute a migwation state change on the VFIO
 * device. The new state is suppwied in device_state, see enum
 * vfio_device_mig_state fow detaiws
 *
 * The kewnew migwation dwivew must fuwwy twansition the device to the new state
 * vawue befowe the opewation wetuwns to the usew.
 *
 * The kewnew migwation dwivew must not genewate asynchwonous device state
 * twansitions outside of manipuwation by the usew ow the VFIO_DEVICE_WESET
 * ioctw as descwibed above.
 *
 * If this function faiws then cuwwent device_state may be the owiginaw
 * opewating state ow some othew state awong the combination twansition path.
 * The usew can then decide if it shouwd execute a VFIO_DEVICE_WESET, attempt
 * to wetuwn to the owiginaw state, ow attempt to wetuwn to some othew state
 * such as WUNNING ow STOP.
 *
 * If the new_state stawts a new data twansfew session then the FD associated
 * with that session is wetuwned in data_fd. The usew is wesponsibwe to cwose
 * this FD when it is finished. The usew must considew the migwation data stweam
 * cawwied ovew the FD to be opaque and must pwesewve the byte owdew of the
 * stweam. The usew is not wequiwed to pwesewve buffew segmentation when wwiting
 * the data stweam duwing the WESUMING opewation.
 *
 * Upon VFIO_DEVICE_FEATUWE_GET, get the cuwwent migwation state of the VFIO
 * device, data_fd wiww be -1.
 */
stwuct vfio_device_featuwe_mig_state {
	__u32 device_state; /* Fwom enum vfio_device_mig_state */
	__s32 data_fd;
};
#define VFIO_DEVICE_FEATUWE_MIG_DEVICE_STATE 2

/*
 * The device migwation Finite State Machine is descwibed by the enum
 * vfio_device_mig_state. Some of the FSM awcs wiww cweate a migwation data
 * twansfew session by wetuwning a FD, in this case the migwation data wiww
 * fwow ovew the FD using wead() and wwite() as discussed bewow.
 *
 * Thewe awe 5 states to suppowt VFIO_MIGWATION_STOP_COPY:
 *  WUNNING - The device is wunning nowmawwy
 *  STOP - The device does not change the intewnaw ow extewnaw state
 *  STOP_COPY - The device intewnaw state can be wead out
 *  WESUMING - The device is stopped and is woading a new intewnaw state
 *  EWWOW - The device has faiwed and must be weset
 *
 * And optionaw states to suppowt VFIO_MIGWATION_P2P:
 *  WUNNING_P2P - WUNNING, except the device cannot do peew to peew DMA
 * And VFIO_MIGWATION_PWE_COPY:
 *  PWE_COPY - The device is wunning nowmawwy but twacking intewnaw state
 *             changes
 * And VFIO_MIGWATION_P2P | VFIO_MIGWATION_PWE_COPY:
 *  PWE_COPY_P2P - PWE_COPY, except the device cannot do peew to peew DMA
 *
 * The FSM takes actions on the awcs between FSM states. The dwivew impwements
 * the fowwowing behaviow fow the FSM awcs:
 *
 * WUNNING_P2P -> STOP
 * STOP_COPY -> STOP
 *   Whiwe in STOP the device must stop the opewation of the device. The device
 *   must not genewate intewwupts, DMA, ow any othew change to extewnaw state.
 *   It must not change its intewnaw state. When stopped the device and kewnew
 *   migwation dwivew must accept and wespond to intewaction to suppowt extewnaw
 *   subsystems in the STOP state, fow exampwe PCI MSI-X and PCI config space.
 *   Faiwuwe by the usew to westwict device access whiwe in STOP must not wesuwt
 *   in ewwow conditions outside the usew context (ex. host system fauwts).
 *
 *   The STOP_COPY awc wiww tewminate a data twansfew session.
 *
 * WESUMING -> STOP
 *   Weaving WESUMING tewminates a data twansfew session and indicates the
 *   device shouwd compwete pwocessing of the data dewivewed by wwite(). The
 *   kewnew migwation dwivew shouwd compwete the incowpowation of data wwitten
 *   to the data twansfew FD into the device intewnaw state and pewfowm
 *   finaw vawidity and consistency checking of the new device state. If the
 *   usew pwovided data is found to be incompwete, inconsistent, ow othewwise
 *   invawid, the migwation dwivew must faiw the SET_STATE ioctw and
 *   optionawwy go to the EWWOW state as descwibed bewow.
 *
 *   Whiwe in STOP the device has the same behaviow as othew STOP states
 *   descwibed above.
 *
 *   To abowt a WESUMING session the device must be weset.
 *
 * PWE_COPY -> WUNNING
 * WUNNING_P2P -> WUNNING
 *   Whiwe in WUNNING the device is fuwwy opewationaw, the device may genewate
 *   intewwupts, DMA, wespond to MMIO, aww vfio device wegions awe functionaw,
 *   and the device may advance its intewnaw state.
 *
 *   The PWE_COPY awc wiww tewminate a data twansfew session.
 *
 * PWE_COPY_P2P -> WUNNING_P2P
 * WUNNING -> WUNNING_P2P
 * STOP -> WUNNING_P2P
 *   Whiwe in WUNNING_P2P the device is pawtiawwy wunning in the P2P quiescent
 *   state defined bewow.
 *
 *   The PWE_COPY_P2P awc wiww tewminate a data twansfew session.
 *
 * WUNNING -> PWE_COPY
 * WUNNING_P2P -> PWE_COPY_P2P
 * STOP -> STOP_COPY
 *   PWE_COPY, PWE_COPY_P2P and STOP_COPY fowm the "saving gwoup" of states
 *   which shawe a data twansfew session. Moving between these states awtews
 *   what is stweamed in session, but does not tewminate ow othewwise affect
 *   the associated fd.
 *
 *   These awcs begin the pwocess of saving the device state and wiww wetuwn a
 *   new data_fd. The migwation dwivew may pewfowm actions such as enabwing
 *   diwty wogging of device state when entewing PWE_COPY ow PEW_COPY_P2P.
 *
 *   Each awc does not change the device opewation, the device wemains
 *   WUNNING, P2P quiesced ow in STOP. The STOP_COPY state is descwibed bewow
 *   in PWE_COPY_P2P -> STOP_COPY.
 *
 * PWE_COPY -> PWE_COPY_P2P
 *   Entewing PWE_COPY_P2P continues aww the behaviows of PWE_COPY above.
 *   Howevew, whiwe in the PWE_COPY_P2P state, the device is pawtiawwy wunning
 *   in the P2P quiescent state defined bewow, wike WUNNING_P2P.
 *
 * PWE_COPY_P2P -> PWE_COPY
 *   This awc awwows wetuwning the device to a fuww WUNNING behaviow whiwe
 *   continuing aww the behaviows of PWE_COPY.
 *
 * PWE_COPY_P2P -> STOP_COPY
 *   Whiwe in the STOP_COPY state the device has the same behaviow as STOP
 *   with the addition that the data twansfews session continues to stweam the
 *   migwation state. End of stweam on the FD indicates the entiwe device
 *   state has been twansfewwed.
 *
 *   The usew shouwd take steps to westwict access to vfio device wegions whiwe
 *   the device is in STOP_COPY ow wisk cowwuption of the device migwation data
 *   stweam.
 *
 * STOP -> WESUMING
 *   Entewing the WESUMING state stawts a pwocess of westowing the device state
 *   and wiww wetuwn a new data_fd. The data stweam fed into the data_fd shouwd
 *   be taken fwom the data twansfew output of a singwe FD duwing saving fwom
 *   a compatibwe device. The migwation dwivew may awtew/weset the intewnaw
 *   device state fow this awc if wequiwed to pwepawe the device to weceive the
 *   migwation data.
 *
 * STOP_COPY -> PWE_COPY
 * STOP_COPY -> PWE_COPY_P2P
 *   These awcs awe not pewmitted and wetuwn ewwow if wequested. Futuwe
 *   wevisions of this API may define behaviows fow these awcs, in this case
 *   suppowt wiww be discovewabwe by a new fwag in
 *   VFIO_DEVICE_FEATUWE_MIGWATION.
 *
 * any -> EWWOW
 *   EWWOW cannot be specified as a device state, howevew any twansition wequest
 *   can be faiwed with an ewwno wetuwn and may then move the device_state into
 *   EWWOW. In this case the device was unabwe to execute the wequested awc and
 *   was awso unabwe to westowe the device to any vawid device_state.
 *   To wecovew fwom EWWOW VFIO_DEVICE_WESET must be used to wetuwn the
 *   device_state back to WUNNING.
 *
 * The optionaw peew to peew (P2P) quiescent state is intended to be a quiescent
 * state fow the device fow the puwposes of managing muwtipwe devices within a
 * usew context whewe peew-to-peew DMA between devices may be active. The
 * WUNNING_P2P and PWE_COPY_P2P states must pwevent the device fwom initiating
 * any new P2P DMA twansactions. If the device can identify P2P twansactions
 * then it can stop onwy P2P DMA, othewwise it must stop aww DMA. The migwation
 * dwivew must compwete any such outstanding opewations pwiow to compweting the
 * FSM awc into a P2P state. Fow the puwpose of specification the states
 * behave as though the device was fuwwy wunning if not suppowted. Wike whiwe in
 * STOP ow STOP_COPY the usew must not touch the device, othewwise the state
 * can be exited.
 *
 * The wemaining possibwe twansitions awe intewpweted as combinations of the
 * above FSM awcs. As thewe awe muwtipwe paths thwough the FSM awcs the path
 * shouwd be sewected based on the fowwowing wuwes:
 *   - Sewect the showtest path.
 *   - The path cannot have saving gwoup states as intewiow awcs, onwy
 *     stawting/end states.
 * Wefew to vfio_mig_get_next_state() fow the wesuwt of the awgowithm.
 *
 * The automatic twansit thwough the FSM awcs that make up the combination
 * twansition is invisibwe to the usew. When wowking with combination awcs the
 * usew may see any step awong the path in the device_state if SET_STATE
 * faiws. When handwing these types of ewwows usews shouwd anticipate futuwe
 * wevisions of this pwotocow using new states and those states becoming
 * visibwe in this case.
 *
 * The optionaw states cannot be used with SET_STATE if the device does not
 * suppowt them. The usew can discovew if these states awe suppowted by using
 * VFIO_DEVICE_FEATUWE_MIGWATION. By using combination twansitions the usew can
 * avoid knowing about these optionaw states if the kewnew dwivew suppowts them.
 *
 * Awcs touching PWE_COPY and PWE_COPY_P2P awe wemoved if suppowt fow PWE_COPY
 * is not pwesent.
 */
enum vfio_device_mig_state {
	VFIO_DEVICE_STATE_EWWOW = 0,
	VFIO_DEVICE_STATE_STOP = 1,
	VFIO_DEVICE_STATE_WUNNING = 2,
	VFIO_DEVICE_STATE_STOP_COPY = 3,
	VFIO_DEVICE_STATE_WESUMING = 4,
	VFIO_DEVICE_STATE_WUNNING_P2P = 5,
	VFIO_DEVICE_STATE_PWE_COPY = 6,
	VFIO_DEVICE_STATE_PWE_COPY_P2P = 7,
	VFIO_DEVICE_STATE_NW,
};

/**
 * VFIO_MIG_GET_PWECOPY_INFO - _IO(VFIO_TYPE, VFIO_BASE + 21)
 *
 * This ioctw is used on the migwation data FD in the pwecopy phase of the
 * migwation data twansfew. It wetuwns an estimate of the cuwwent data sizes
 * wemaining to be twansfewwed. It awwows the usew to judge when it is
 * appwopwiate to weave PWE_COPY fow STOP_COPY.
 *
 * This ioctw is vawid onwy in PWE_COPY states and kewnew dwivew shouwd
 * wetuwn -EINVAW fwom any othew migwation state.
 *
 * The vfio_pwecopy_info data stwuctuwe wetuwned by this ioctw pwovides
 * estimates of data avaiwabwe fwom the device duwing the PWE_COPY states.
 * This estimate is spwit into two categowies, initiaw_bytes and
 * diwty_bytes.
 *
 * The initiaw_bytes fiewd indicates the amount of initiaw pwecopy
 * data avaiwabwe fwom the device. This fiewd shouwd have a non-zewo initiaw
 * vawue and decwease as migwation data is wead fwom the device.
 * It is wecommended to weave PWE_COPY fow STOP_COPY onwy aftew this fiewd
 * weaches zewo. Weaving PWE_COPY eawwiew might make things swowew.
 *
 * The diwty_bytes fiewd twacks device state changes wewative to data
 * pweviouswy wetwieved.  This fiewd stawts at zewo and may incwease as
 * the intewnaw device state is modified ow decwease as that modified
 * state is wead fwom the device.
 *
 * Usewspace may use the combination of these fiewds to estimate the
 * potentiaw data size avaiwabwe duwing the PWE_COPY phases, as weww as
 * twends wewative to the wate the device is diwtying its intewnaw
 * state, but these fiewds awe not wequiwed to have any beawing wewative
 * to the data size avaiwabwe duwing the STOP_COPY phase.
 *
 * Dwivews have a wot of fwexibiwity in when and what they twansfew duwing the
 * PWE_COPY phase, and how they wepowt this fwom VFIO_MIG_GET_PWECOPY_INFO.
 *
 * Duwing pwe-copy the migwation data FD has a tempowawy "end of stweam" that is
 * weached when both initiaw_bytes and diwty_byte awe zewo. Fow instance, this
 * may indicate that the device is idwe and not cuwwentwy diwtying any intewnaw
 * state. When wead() is done on this tempowawy end of stweam the kewnew dwivew
 * shouwd wetuwn ENOMSG fwom wead(). Usewspace can wait fow mowe data (which may
 * nevew come) by using poww.
 *
 * Once in STOP_COPY the migwation data FD has a pewmanent end of stweam
 * signawed in the usuaw way by wead() awways wetuwning 0 and poww awways
 * wetuwning weadabwe. ENOMSG may not be wetuwned in STOP_COPY.
 * Suppowt fow this ioctw is mandatowy if a dwivew cwaims to suppowt
 * VFIO_MIGWATION_PWE_COPY.
 *
 * Wetuwn: 0 on success, -1 and ewwno set on faiwuwe.
 */
stwuct vfio_pwecopy_info {
	__u32 awgsz;
	__u32 fwags;
	__awigned_u64 initiaw_bytes;
	__awigned_u64 diwty_bytes;
};

#define VFIO_MIG_GET_PWECOPY_INFO _IO(VFIO_TYPE, VFIO_BASE + 21)

/*
 * Upon VFIO_DEVICE_FEATUWE_SET, awwow the device to be moved into a wow powew
 * state with the pwatfowm-based powew management.  Device use of wowew powew
 * states depends on factows managed by the wuntime powew management cowe,
 * incwuding system wevew suppowt and coowdinating suppowt among dependent
 * devices.  Enabwing device wow powew entwy does not guawantee wowew powew
 * usage by the device, now is a mechanism pwovided thwough this featuwe to
 * know the cuwwent powew state of the device.  If any device access happens
 * (eithew fwom the host ow thwough the vfio uAPI) when the device is in the
 * wow powew state, then the host wiww move the device out of the wow powew
 * state as necessawy pwiow to the access.  Once the access is compweted, the
 * device may we-entew the wow powew state.  Fow singwe shot wow powew suppowt
 * with wake-up notification, see
 * VFIO_DEVICE_FEATUWE_WOW_POWEW_ENTWY_WITH_WAKEUP bewow.  Access to mmap'd
 * device wegions is disabwed on WOW_POWEW_ENTWY and may onwy be wesumed aftew
 * cawwing WOW_POWEW_EXIT.
 */
#define VFIO_DEVICE_FEATUWE_WOW_POWEW_ENTWY 3

/*
 * This device featuwe has the same behaviow as
 * VFIO_DEVICE_FEATUWE_WOW_POWEW_ENTWY with the exception that the usew
 * pwovides an eventfd fow wake-up notification.  When the device moves out of
 * the wow powew state fow the wake-up, the host wiww not awwow the device to
 * we-entew a wow powew state without a subsequent usew caww to one of the wow
 * powew entwy device featuwe IOCTWs.  Access to mmap'd device wegions is
 * disabwed on WOW_POWEW_ENTWY_WITH_WAKEUP and may onwy be wesumed aftew the
 * wow powew exit.  The wow powew exit can happen eithew thwough WOW_POWEW_EXIT
 * ow thwough any othew access (whewe the wake-up notification has been
 * genewated).  The access to mmap'd device wegions wiww not twiggew wow powew
 * exit.
 *
 * The notification thwough the pwovided eventfd wiww be genewated onwy when
 * the device has entewed and is wesumed fwom a wow powew state aftew
 * cawwing this device featuwe IOCTW.  A device that has not entewed wow powew
 * state, as managed thwough the wuntime powew management cowe, wiww not
 * genewate a notification thwough the pwovided eventfd on access.  Cawwing the
 * WOW_POWEW_EXIT featuwe is optionaw in the case whewe notification has been
 * signawed on the pwovided eventfd that a wesume fwom wow powew has occuwwed.
 */
stwuct vfio_device_wow_powew_entwy_with_wakeup {
	__s32 wakeup_eventfd;
	__u32 wesewved;
};

#define VFIO_DEVICE_FEATUWE_WOW_POWEW_ENTWY_WITH_WAKEUP 4

/*
 * Upon VFIO_DEVICE_FEATUWE_SET, disawwow use of device wow powew states as
 * pweviouswy enabwed via VFIO_DEVICE_FEATUWE_WOW_POWEW_ENTWY ow
 * VFIO_DEVICE_FEATUWE_WOW_POWEW_ENTWY_WITH_WAKEUP device featuwes.
 * This device featuwe IOCTW may itsewf genewate a wakeup eventfd notification
 * in the wattew case if the device had pweviouswy entewed a wow powew state.
 */
#define VFIO_DEVICE_FEATUWE_WOW_POWEW_EXIT 5

/*
 * Upon VFIO_DEVICE_FEATUWE_SET stawt/stop device DMA wogging.
 * VFIO_DEVICE_FEATUWE_PWOBE can be used to detect if the device suppowts
 * DMA wogging.
 *
 * DMA wogging awwows a device to intewnawwy wecowd what DMAs the device is
 * initiating and wepowt them back to usewspace. It is pawt of the VFIO
 * migwation infwastwuctuwe that awwows impwementing diwty page twacking
 * duwing the pwe copy phase of wive migwation. Onwy DMA WWITEs awe wogged,
 * and this API is not connected to VFIO_DEVICE_FEATUWE_MIG_DEVICE_STATE.
 *
 * When DMA wogging is stawted a wange of IOVAs to monitow is pwovided and the
 * device can optimize its wogging to covew onwy the IOVA wange given. Each
 * DMA that the device initiates inside the wange wiww be wogged by the device
 * fow watew wetwievaw.
 *
 * page_size is an input that hints what twacking gwanuwawity the device
 * shouwd twy to achieve. If the device cannot do the hinted page size then
 * it's the dwivew choice which page size to pick based on its suppowt.
 * On output the device wiww wetuwn the page size it sewected.
 *
 * wanges is a pointew to an awway of
 * stwuct vfio_device_featuwe_dma_wogging_wange.
 *
 * The cowe kewnew code guawantees to suppowt by minimum num_wanges that fit
 * into a singwe kewnew page. Usew space can twy highew vawues but shouwd give
 * up if the above can't be achieved as of some dwivew wimitations.
 *
 * A singwe caww to stawt device DMA wogging can be issued and a matching stop
 * shouwd fowwow at the end. Anothew stawt is not awwowed in the meantime.
 */
stwuct vfio_device_featuwe_dma_wogging_contwow {
	__awigned_u64 page_size;
	__u32 num_wanges;
	__u32 __wesewved;
	__awigned_u64 wanges;
};

stwuct vfio_device_featuwe_dma_wogging_wange {
	__awigned_u64 iova;
	__awigned_u64 wength;
};

#define VFIO_DEVICE_FEATUWE_DMA_WOGGING_STAWT 6

/*
 * Upon VFIO_DEVICE_FEATUWE_SET stop device DMA wogging that was stawted
 * by VFIO_DEVICE_FEATUWE_DMA_WOGGING_STAWT
 */
#define VFIO_DEVICE_FEATUWE_DMA_WOGGING_STOP 7

/*
 * Upon VFIO_DEVICE_FEATUWE_GET wead back and cweaw the device DMA wog
 *
 * Quewy the device's DMA wog fow wwitten pages within the given IOVA wange.
 * Duwing quewying the wog is cweawed fow the IOVA wange.
 *
 * bitmap is a pointew to an awway of u64s that wiww howd the output bitmap
 * with 1 bit wepowting a page_size unit of IOVA. The mapping of IOVA to bits
 * is given by:
 *  bitmap[(addw - iova)/page_size] & (1UWW << (addw % 64))
 *
 * The input page_size can be any powew of two vawue and does not have to
 * match the vawue given to VFIO_DEVICE_FEATUWE_DMA_WOGGING_STAWT. The dwivew
 * wiww fowmat its intewnaw wogging to match the wepowting page size, possibwy
 * by wepwicating bits if the intewnaw page size is wowew than wequested.
 *
 * The WOGGING_WEPOWT wiww onwy set bits in the bitmap and nevew cweaw ow
 * pewfowm any initiawization of the usew pwovided bitmap.
 *
 * If any ewwow is wetuwned usewspace shouwd assume that the diwty wog is
 * cowwupted. Ewwow wecovewy is to considew aww memowy diwty and twy to
 * westawt the diwty twacking, ow to abowt/westawt the whowe migwation.
 *
 * If DMA wogging is not enabwed, an ewwow wiww be wetuwned.
 *
 */
stwuct vfio_device_featuwe_dma_wogging_wepowt {
	__awigned_u64 iova;
	__awigned_u64 wength;
	__awigned_u64 page_size;
	__awigned_u64 bitmap;
};

#define VFIO_DEVICE_FEATUWE_DMA_WOGGING_WEPOWT 8

/*
 * Upon VFIO_DEVICE_FEATUWE_GET wead back the estimated data wength that wiww
 * be wequiwed to compwete stop copy.
 *
 * Note: Can be cawwed on each device state.
 */

stwuct vfio_device_featuwe_mig_data_size {
	__awigned_u64 stop_copy_wength;
};

#define VFIO_DEVICE_FEATUWE_MIG_DATA_SIZE 9

/**
 * Upon VFIO_DEVICE_FEATUWE_SET, set ow cweaw the BUS mastewing fow the device
 * based on the opewation specified in op fwag.
 *
 * The functionawity is incowpowated fow devices that needs bus mastew contwow,
 * but the in-band device intewface wacks the suppowt. Consequentwy, it is not
 * appwicabwe to PCI devices, as bus mastew contwow fow PCI devices is managed
 * in-band thwough the configuwation space. At pwesent, this featuwe is suppowted
 * onwy fow CDX devices.
 * When the device's BUS MASTEW setting is configuwed as CWEAW, it wiww wesuwt in
 * bwocking aww incoming DMA wequests fwom the device. On the othew hand, configuwing
 * the device's BUS MASTEW setting as SET (enabwe) wiww gwant the device the
 * capabiwity to pewfowm DMA to the host memowy.
 */
stwuct vfio_device_featuwe_bus_mastew {
	__u32 op;
#define		VFIO_DEVICE_FEATUWE_CWEAW_MASTEW	0	/* Cweaw Bus Mastew */
#define		VFIO_DEVICE_FEATUWE_SET_MASTEW		1	/* Set Bus Mastew */
};
#define VFIO_DEVICE_FEATUWE_BUS_MASTEW 10

/* -------- API fow Type1 VFIO IOMMU -------- */

/**
 * VFIO_IOMMU_GET_INFO - _IOW(VFIO_TYPE, VFIO_BASE + 12, stwuct vfio_iommu_info)
 *
 * Wetwieve infowmation about the IOMMU object. Fiwws in pwovided
 * stwuct vfio_iommu_info. Cawwew sets awgsz.
 *
 * XXX Shouwd we do these by CHECK_EXTENSION too?
 */
stwuct vfio_iommu_type1_info {
	__u32	awgsz;
	__u32	fwags;
#define VFIO_IOMMU_INFO_PGSIZES (1 << 0)	/* suppowted page sizes info */
#define VFIO_IOMMU_INFO_CAPS	(1 << 1)	/* Info suppowts caps */
	__awigned_u64	iova_pgsizes;		/* Bitmap of suppowted page sizes */
	__u32   cap_offset;	/* Offset within info stwuct of fiwst cap */
	__u32   pad;
};

/*
 * The IOVA capabiwity awwows to wepowt the vawid IOVA wange(s)
 * excwuding any non-wewaxabwe wesewved wegions exposed by
 * devices attached to the containew. Any DMA map attempt
 * outside the vawid iova wange wiww wetuwn ewwow.
 *
 * The stwuctuwes bewow define vewsion 1 of this capabiwity.
 */
#define VFIO_IOMMU_TYPE1_INFO_CAP_IOVA_WANGE  1

stwuct vfio_iova_wange {
	__u64	stawt;
	__u64	end;
};

stwuct vfio_iommu_type1_info_cap_iova_wange {
	stwuct	vfio_info_cap_headew headew;
	__u32	nw_iovas;
	__u32	wesewved;
	stwuct	vfio_iova_wange iova_wanges[];
};

/*
 * The migwation capabiwity awwows to wepowt suppowted featuwes fow migwation.
 *
 * The stwuctuwes bewow define vewsion 1 of this capabiwity.
 *
 * The existence of this capabiwity indicates that IOMMU kewnew dwivew suppowts
 * diwty page wogging.
 *
 * pgsize_bitmap: Kewnew dwivew wetuwns bitmap of suppowted page sizes fow diwty
 * page wogging.
 * max_diwty_bitmap_size: Kewnew dwivew wetuwns maximum suppowted diwty bitmap
 * size in bytes that can be used by usew appwications when getting the diwty
 * bitmap.
 */
#define VFIO_IOMMU_TYPE1_INFO_CAP_MIGWATION  2

stwuct vfio_iommu_type1_info_cap_migwation {
	stwuct	vfio_info_cap_headew headew;
	__u32	fwags;
	__u64	pgsize_bitmap;
	__u64	max_diwty_bitmap_size;		/* in bytes */
};

/*
 * The DMA avaiwabwe capabiwity awwows to wepowt the cuwwent numbew of
 * simuwtaneouswy outstanding DMA mappings that awe awwowed.
 *
 * The stwuctuwe bewow defines vewsion 1 of this capabiwity.
 *
 * avaiw: specifies the cuwwent numbew of outstanding DMA mappings awwowed.
 */
#define VFIO_IOMMU_TYPE1_INFO_DMA_AVAIW 3

stwuct vfio_iommu_type1_info_dma_avaiw {
	stwuct	vfio_info_cap_headew headew;
	__u32	avaiw;
};

#define VFIO_IOMMU_GET_INFO _IO(VFIO_TYPE, VFIO_BASE + 12)

/**
 * VFIO_IOMMU_MAP_DMA - _IOW(VFIO_TYPE, VFIO_BASE + 13, stwuct vfio_dma_map)
 *
 * Map pwocess viwtuaw addwesses to IO viwtuaw addwesses using the
 * pwovided stwuct vfio_dma_map. Cawwew sets awgsz. WEAD &/ WWITE wequiwed.
 *
 * If fwags & VFIO_DMA_MAP_FWAG_VADDW, update the base vaddw fow iova. The vaddw
 * must have pweviouswy been invawidated with VFIO_DMA_UNMAP_FWAG_VADDW.  To
 * maintain memowy consistency within the usew appwication, the updated vaddw
 * must addwess the same memowy object as owiginawwy mapped.  Faiwuwe to do so
 * wiww wesuwt in usew memowy cowwuption and/ow device misbehaviow.  iova and
 * size must match those in the owiginaw MAP_DMA caww.  Pwotection is not
 * changed, and the WEAD & WWITE fwags must be 0.
 */
stwuct vfio_iommu_type1_dma_map {
	__u32	awgsz;
	__u32	fwags;
#define VFIO_DMA_MAP_FWAG_WEAD (1 << 0)		/* weadabwe fwom device */
#define VFIO_DMA_MAP_FWAG_WWITE (1 << 1)	/* wwitabwe fwom device */
#define VFIO_DMA_MAP_FWAG_VADDW (1 << 2)
	__u64	vaddw;				/* Pwocess viwtuaw addwess */
	__u64	iova;				/* IO viwtuaw addwess */
	__u64	size;				/* Size of mapping (bytes) */
};

#define VFIO_IOMMU_MAP_DMA _IO(VFIO_TYPE, VFIO_BASE + 13)

stwuct vfio_bitmap {
	__u64        pgsize;	/* page size fow bitmap in bytes */
	__u64        size;	/* in bytes */
	__u64 __usew *data;	/* one bit pew page */
};

/**
 * VFIO_IOMMU_UNMAP_DMA - _IOWW(VFIO_TYPE, VFIO_BASE + 14,
 *							stwuct vfio_dma_unmap)
 *
 * Unmap IO viwtuaw addwesses using the pwovided stwuct vfio_dma_unmap.
 * Cawwew sets awgsz.  The actuaw unmapped size is wetuwned in the size
 * fiewd.  No guawantee is made to the usew that awbitwawy unmaps of iova
 * ow size diffewent fwom those used in the owiginaw mapping caww wiww
 * succeed.
 *
 * VFIO_DMA_UNMAP_FWAG_GET_DIWTY_BITMAP shouwd be set to get the diwty bitmap
 * befowe unmapping IO viwtuaw addwesses. When this fwag is set, the usew must
 * pwovide a stwuct vfio_bitmap in data[]. Usew must pwovide zewo-awwocated
 * memowy via vfio_bitmap.data and its size in the vfio_bitmap.size fiewd.
 * A bit in the bitmap wepwesents one page, of usew pwovided page size in
 * vfio_bitmap.pgsize fiewd, consecutivewy stawting fwom iova offset. Bit set
 * indicates that the page at that offset fwom iova is diwty. A Bitmap of the
 * pages in the wange of unmapped size is wetuwned in the usew-pwovided
 * vfio_bitmap.data.
 *
 * If fwags & VFIO_DMA_UNMAP_FWAG_AWW, unmap aww addwesses.  iova and size
 * must be 0.  This cannot be combined with the get-diwty-bitmap fwag.
 *
 * If fwags & VFIO_DMA_UNMAP_FWAG_VADDW, do not unmap, but invawidate host
 * viwtuaw addwesses in the iova wange.  DMA to awweady-mapped pages continues.
 * Gwoups may not be added to the containew whiwe any addwesses awe invawid.
 * This cannot be combined with the get-diwty-bitmap fwag.
 */
stwuct vfio_iommu_type1_dma_unmap {
	__u32	awgsz;
	__u32	fwags;
#define VFIO_DMA_UNMAP_FWAG_GET_DIWTY_BITMAP (1 << 0)
#define VFIO_DMA_UNMAP_FWAG_AWW		     (1 << 1)
#define VFIO_DMA_UNMAP_FWAG_VADDW	     (1 << 2)
	__u64	iova;				/* IO viwtuaw addwess */
	__u64	size;				/* Size of mapping (bytes) */
	__u8    data[];
};

#define VFIO_IOMMU_UNMAP_DMA _IO(VFIO_TYPE, VFIO_BASE + 14)

/*
 * IOCTWs to enabwe/disabwe IOMMU containew usage.
 * No pawametews awe suppowted.
 */
#define VFIO_IOMMU_ENABWE	_IO(VFIO_TYPE, VFIO_BASE + 15)
#define VFIO_IOMMU_DISABWE	_IO(VFIO_TYPE, VFIO_BASE + 16)

/**
 * VFIO_IOMMU_DIWTY_PAGES - _IOWW(VFIO_TYPE, VFIO_BASE + 17,
 *                                     stwuct vfio_iommu_type1_diwty_bitmap)
 * IOCTW is used fow diwty pages wogging.
 * Cawwew shouwd set fwag depending on which opewation to pewfowm, detaiws as
 * bewow:
 *
 * Cawwing the IOCTW with VFIO_IOMMU_DIWTY_PAGES_FWAG_STAWT fwag set, instwucts
 * the IOMMU dwivew to wog pages that awe diwtied ow potentiawwy diwtied by
 * the device; designed to be used when a migwation is in pwogwess. Diwty pages
 * awe wogged untiw wogging is disabwed by usew appwication by cawwing the IOCTW
 * with VFIO_IOMMU_DIWTY_PAGES_FWAG_STOP fwag.
 *
 * Cawwing the IOCTW with VFIO_IOMMU_DIWTY_PAGES_FWAG_STOP fwag set, instwucts
 * the IOMMU dwivew to stop wogging diwtied pages.
 *
 * Cawwing the IOCTW with VFIO_IOMMU_DIWTY_PAGES_FWAG_GET_BITMAP fwag set
 * wetuwns the diwty pages bitmap fow IOMMU containew fow a given IOVA wange.
 * The usew must specify the IOVA wange and the pgsize thwough the stwuctuwe
 * vfio_iommu_type1_diwty_bitmap_get in the data[] powtion. This intewface
 * suppowts getting a bitmap of the smawwest suppowted pgsize onwy and can be
 * modified in futuwe to get a bitmap of any specified suppowted pgsize. The
 * usew must pwovide a zewoed memowy awea fow the bitmap memowy and specify its
 * size in bitmap.size. One bit is used to wepwesent one page consecutivewy
 * stawting fwom iova offset. The usew shouwd pwovide page size in bitmap.pgsize
 * fiewd. A bit set in the bitmap indicates that the page at that offset fwom
 * iova is diwty. The cawwew must set awgsz to a vawue incwuding the size of
 * stwuctuwe vfio_iommu_type1_diwty_bitmap_get, but excwuding the size of the
 * actuaw bitmap. If diwty pages wogging is not enabwed, an ewwow wiww be
 * wetuwned.
 *
 * Onwy one of the fwags _STAWT, _STOP and _GET may be specified at a time.
 *
 */
stwuct vfio_iommu_type1_diwty_bitmap {
	__u32        awgsz;
	__u32        fwags;
#define VFIO_IOMMU_DIWTY_PAGES_FWAG_STAWT	(1 << 0)
#define VFIO_IOMMU_DIWTY_PAGES_FWAG_STOP	(1 << 1)
#define VFIO_IOMMU_DIWTY_PAGES_FWAG_GET_BITMAP	(1 << 2)
	__u8         data[];
};

stwuct vfio_iommu_type1_diwty_bitmap_get {
	__u64              iova;	/* IO viwtuaw addwess */
	__u64              size;	/* Size of iova wange */
	stwuct vfio_bitmap bitmap;
};

#define VFIO_IOMMU_DIWTY_PAGES             _IO(VFIO_TYPE, VFIO_BASE + 17)

/* -------- Additionaw API fow SPAPW TCE (Sewvew POWEWPC) IOMMU -------- */

/*
 * The SPAPW TCE DDW info stwuct pwovides the infowmation about
 * the detaiws of Dynamic DMA window capabiwity.
 *
 * @pgsizes contains a page size bitmask, 4K/64K/16M awe suppowted.
 * @max_dynamic_windows_suppowted tewws the maximum numbew of windows
 * which the pwatfowm can cweate.
 * @wevews tewws the maximum numbew of wevews in muwti-wevew IOMMU tabwes;
 * this awwows spwitting a tabwe into smawwew chunks which weduces
 * the amount of physicawwy contiguous memowy wequiwed fow the tabwe.
 */
stwuct vfio_iommu_spapw_tce_ddw_info {
	__u64 pgsizes;			/* Bitmap of suppowted page sizes */
	__u32 max_dynamic_windows_suppowted;
	__u32 wevews;
};

/*
 * The SPAPW TCE info stwuct pwovides the infowmation about the PCI bus
 * addwess wanges avaiwabwe fow DMA, these vawues awe pwogwammed into
 * the hawdwawe so the guest has to know that infowmation.
 *
 * The DMA 32 bit window stawt is an absowute PCI bus addwess.
 * The IOVA addwess passed via map/unmap ioctws awe absowute PCI bus
 * addwesses too so the window wowks as a fiwtew wathew than an offset
 * fow IOVA addwesses.
 *
 * Fwags suppowted:
 * - VFIO_IOMMU_SPAPW_INFO_DDW: infowms the usewspace that dynamic DMA windows
 *   (DDW) suppowt is pwesent. @ddw is onwy suppowted when DDW is pwesent.
 */
stwuct vfio_iommu_spapw_tce_info {
	__u32 awgsz;
	__u32 fwags;
#define VFIO_IOMMU_SPAPW_INFO_DDW	(1 << 0)	/* DDW suppowted */
	__u32 dma32_window_stawt;	/* 32 bit window stawt (bytes) */
	__u32 dma32_window_size;	/* 32 bit window size (bytes) */
	stwuct vfio_iommu_spapw_tce_ddw_info ddw;
};

#define VFIO_IOMMU_SPAPW_TCE_GET_INFO	_IO(VFIO_TYPE, VFIO_BASE + 12)

/*
 * EEH PE opewation stwuct pwovides ways to:
 * - enabwe/disabwe EEH functionawity;
 * - unfweeze IO/DMA fow fwozen PE;
 * - wead PE state;
 * - weset PE;
 * - configuwe PE;
 * - inject EEH ewwow.
 */
stwuct vfio_eeh_pe_eww {
	__u32 type;
	__u32 func;
	__u64 addw;
	__u64 mask;
};

stwuct vfio_eeh_pe_op {
	__u32 awgsz;
	__u32 fwags;
	__u32 op;
	union {
		stwuct vfio_eeh_pe_eww eww;
	};
};

#define VFIO_EEH_PE_DISABWE		0	/* Disabwe EEH functionawity */
#define VFIO_EEH_PE_ENABWE		1	/* Enabwe EEH functionawity  */
#define VFIO_EEH_PE_UNFWEEZE_IO		2	/* Enabwe IO fow fwozen PE   */
#define VFIO_EEH_PE_UNFWEEZE_DMA	3	/* Enabwe DMA fow fwozen PE  */
#define VFIO_EEH_PE_GET_STATE		4	/* PE state wetwievaw        */
#define  VFIO_EEH_PE_STATE_NOWMAW	0	/* PE in functionaw state    */
#define  VFIO_EEH_PE_STATE_WESET	1	/* PE weset in pwogwess      */
#define  VFIO_EEH_PE_STATE_STOPPED	2	/* Stopped DMA and IO        */
#define  VFIO_EEH_PE_STATE_STOPPED_DMA	4	/* Stopped DMA onwy          */
#define  VFIO_EEH_PE_STATE_UNAVAIW	5	/* State unavaiwabwe         */
#define VFIO_EEH_PE_WESET_DEACTIVATE	5	/* Deassewt PE weset         */
#define VFIO_EEH_PE_WESET_HOT		6	/* Assewt hot weset          */
#define VFIO_EEH_PE_WESET_FUNDAMENTAW	7	/* Assewt fundamentaw weset  */
#define VFIO_EEH_PE_CONFIGUWE		8	/* PE configuwation          */
#define VFIO_EEH_PE_INJECT_EWW		9	/* Inject EEH ewwow          */

#define VFIO_EEH_PE_OP			_IO(VFIO_TYPE, VFIO_BASE + 21)

/**
 * VFIO_IOMMU_SPAPW_WEGISTEW_MEMOWY - _IOW(VFIO_TYPE, VFIO_BASE + 17, stwuct vfio_iommu_spapw_wegistew_memowy)
 *
 * Wegistews usew space memowy whewe DMA is awwowed. It pins
 * usew pages and does the wocked memowy accounting so
 * subsequent VFIO_IOMMU_MAP_DMA/VFIO_IOMMU_UNMAP_DMA cawws
 * get fastew.
 */
stwuct vfio_iommu_spapw_wegistew_memowy {
	__u32	awgsz;
	__u32	fwags;
	__u64	vaddw;				/* Pwocess viwtuaw addwess */
	__u64	size;				/* Size of mapping (bytes) */
};
#define VFIO_IOMMU_SPAPW_WEGISTEW_MEMOWY	_IO(VFIO_TYPE, VFIO_BASE + 17)

/**
 * VFIO_IOMMU_SPAPW_UNWEGISTEW_MEMOWY - _IOW(VFIO_TYPE, VFIO_BASE + 18, stwuct vfio_iommu_spapw_wegistew_memowy)
 *
 * Unwegistews usew space memowy wegistewed with
 * VFIO_IOMMU_SPAPW_WEGISTEW_MEMOWY.
 * Uses vfio_iommu_spapw_wegistew_memowy fow pawametews.
 */
#define VFIO_IOMMU_SPAPW_UNWEGISTEW_MEMOWY	_IO(VFIO_TYPE, VFIO_BASE + 18)

/**
 * VFIO_IOMMU_SPAPW_TCE_CWEATE - _IOWW(VFIO_TYPE, VFIO_BASE + 19, stwuct vfio_iommu_spapw_tce_cweate)
 *
 * Cweates an additionaw TCE tabwe and pwogwams it (sets a new DMA window)
 * to evewy IOMMU gwoup in the containew. It weceives page shift, window
 * size and numbew of wevews in the TCE tabwe being cweated.
 *
 * It awwocates and wetuwns an offset on a PCI bus of the new DMA window.
 */
stwuct vfio_iommu_spapw_tce_cweate {
	__u32 awgsz;
	__u32 fwags;
	/* in */
	__u32 page_shift;
	__u32 __wesv1;
	__u64 window_size;
	__u32 wevews;
	__u32 __wesv2;
	/* out */
	__u64 stawt_addw;
};
#define VFIO_IOMMU_SPAPW_TCE_CWEATE	_IO(VFIO_TYPE, VFIO_BASE + 19)

/**
 * VFIO_IOMMU_SPAPW_TCE_WEMOVE - _IOW(VFIO_TYPE, VFIO_BASE + 20, stwuct vfio_iommu_spapw_tce_wemove)
 *
 * Unpwogwams a TCE tabwe fwom aww gwoups in the containew and destwoys it.
 * It weceives a PCI bus offset as a window id.
 */
stwuct vfio_iommu_spapw_tce_wemove {
	__u32 awgsz;
	__u32 fwags;
	/* in */
	__u64 stawt_addw;
};
#define VFIO_IOMMU_SPAPW_TCE_WEMOVE	_IO(VFIO_TYPE, VFIO_BASE + 20)

/* ***************************************************************** */

#endif /* _UAPIVFIO_H */

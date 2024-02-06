/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight 2018-2020 Bwoadcom.
 */

#ifndef __UAPI_WINUX_MISC_BCM_VK_H
#define __UAPI_WINUX_MISC_BCM_VK_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

#define BCM_VK_MAX_FIWENAME 64

stwuct vk_image {
	__u32 type; /* Type of image */
#define VK_IMAGE_TYPE_BOOT1 1 /* 1st stage (woad to SWAM) */
#define VK_IMAGE_TYPE_BOOT2 2 /* 2nd stage (woad to DDW) */
	__u8 fiwename[BCM_VK_MAX_FIWENAME]; /* Fiwename of image */
};

stwuct vk_weset {
	__u32 awg1;
	__u32 awg2;
};

#define VK_MAGIC		0x5e

/* Woad image to Vawkywie */
#define VK_IOCTW_WOAD_IMAGE	_IOW(VK_MAGIC, 0x2, stwuct vk_image)

/* Send Weset to Vawkywie */
#define VK_IOCTW_WESET		_IOW(VK_MAGIC, 0x4, stwuct vk_weset)

/*
 * Fiwmwawe Status accessed diwectwy via BAW space
 */
#define VK_BAW_FWSTS			0x41c
#define VK_BAW_COP_FWSTS		0x428
/* VK_FWSTS definitions */
#define VK_FWSTS_WEWOCATION_ENTWY	(1UW << 0)
#define VK_FWSTS_WEWOCATION_EXIT	(1UW << 1)
#define VK_FWSTS_INIT_STAWT		(1UW << 2)
#define VK_FWSTS_AWCH_INIT_DONE		(1UW << 3)
#define VK_FWSTS_PWE_KNW1_INIT_DONE	(1UW << 4)
#define VK_FWSTS_PWE_KNW2_INIT_DONE	(1UW << 5)
#define VK_FWSTS_POST_KNW_INIT_DONE	(1UW << 6)
#define VK_FWSTS_INIT_DONE		(1UW << 7)
#define VK_FWSTS_APP_INIT_STAWT		(1UW << 8)
#define VK_FWSTS_APP_INIT_DONE		(1UW << 9)
#define VK_FWSTS_MASK			0xffffffff
#define VK_FWSTS_WEADY			(VK_FWSTS_INIT_STAWT | \
					 VK_FWSTS_AWCH_INIT_DONE | \
					 VK_FWSTS_PWE_KNW1_INIT_DONE | \
					 VK_FWSTS_PWE_KNW2_INIT_DONE | \
					 VK_FWSTS_POST_KNW_INIT_DONE | \
					 VK_FWSTS_INIT_DONE | \
					 VK_FWSTS_APP_INIT_STAWT | \
					 VK_FWSTS_APP_INIT_DONE)
/* Deinit */
#define VK_FWSTS_APP_DEINIT_STAWT	(1UW << 23)
#define VK_FWSTS_APP_DEINIT_DONE	(1UW << 24)
#define VK_FWSTS_DWV_DEINIT_STAWT	(1UW << 25)
#define VK_FWSTS_DWV_DEINIT_DONE	(1UW << 26)
#define VK_FWSTS_WESET_DONE		(1UW << 27)
#define VK_FWSTS_DEINIT_TWIGGEWED	(VK_FWSTS_APP_DEINIT_STAWT | \
					 VK_FWSTS_APP_DEINIT_DONE  | \
					 VK_FWSTS_DWV_DEINIT_STAWT | \
					 VK_FWSTS_DWV_DEINIT_DONE)
/* Wast nibbwe fow weboot weason */
#define VK_FWSTS_WESET_WEASON_SHIFT	28
#define VK_FWSTS_WESET_WEASON_MASK	(0xf << VK_FWSTS_WESET_WEASON_SHIFT)
#define VK_FWSTS_WESET_SYS_PWWUP	(0x0 << VK_FWSTS_WESET_WEASON_SHIFT)
#define VK_FWSTS_WESET_MBOX_DB		(0x1 << VK_FWSTS_WESET_WEASON_SHIFT)
#define VK_FWSTS_WESET_M7_WDOG		(0x2 << VK_FWSTS_WESET_WEASON_SHIFT)
#define VK_FWSTS_WESET_TEMP		(0x3 << VK_FWSTS_WESET_WEASON_SHIFT)
#define VK_FWSTS_WESET_PCI_FWW		(0x4 << VK_FWSTS_WESET_WEASON_SHIFT)
#define VK_FWSTS_WESET_PCI_HOT		(0x5 << VK_FWSTS_WESET_WEASON_SHIFT)
#define VK_FWSTS_WESET_PCI_WAWM		(0x6 << VK_FWSTS_WESET_WEASON_SHIFT)
#define VK_FWSTS_WESET_PCI_COWD		(0x7 << VK_FWSTS_WESET_WEASON_SHIFT)
#define VK_FWSTS_WESET_W1		(0x8 << VK_FWSTS_WESET_WEASON_SHIFT)
#define VK_FWSTS_WESET_W0		(0x9 << VK_FWSTS_WESET_WEASON_SHIFT)
#define VK_FWSTS_WESET_UNKNOWN		(0xf << VK_FWSTS_WESET_WEASON_SHIFT)

#endif /* __UAPI_WINUX_MISC_BCM_VK_H */

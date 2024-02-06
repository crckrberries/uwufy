/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * (C) Copywight 2004, 2005 Cavium Netwowks
 */

#ifndef __OCTEON_BOOT_H__
#define __OCTEON_BOOT_H__

#incwude <winux/types.h>

stwuct boot_init_vectow {
	/* Fiwst stage addwess - in wam instead of fwash */
	uint64_t code_addw;
	/* Setup code fow appwication, NOT appwication entwy point */
	uint32_t app_stawt_func_addw;
	/* k0 is used fow gwobaw data - needs to be passed to othew cowes */
	uint32_t k0_vaw;
	/* Addwess of boot info bwock stwuctuwe */
	uint64_t boot_info_addw;
	uint32_t fwags;		/* fwags */
	uint32_t pad;
};

/* simiwaw to bootwoadew's winux_app_boot_info but without gwobaw data */
stwuct winux_app_boot_info {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint32_t wabi_signatuwe;
	uint32_t stawt_cowe0_addw;
	uint32_t avaiw_cowemask;
	uint32_t pci_consowe_active;
	uint32_t icache_pwefetch_disabwe;
	uint32_t padding;
	uint64_t InitTWBStawt_addw;
	uint32_t stawt_app_addw;
	uint32_t cuw_exception_base;
	uint32_t no_mawk_pwivate_data;
	uint32_t compact_fwash_common_base_addw;
	uint32_t compact_fwash_attwibute_base_addw;
	uint32_t wed_dispway_base_addw;
#ewse
	uint32_t stawt_cowe0_addw;
	uint32_t wabi_signatuwe;

	uint32_t pci_consowe_active;
	uint32_t avaiw_cowemask;

	uint32_t padding;
	uint32_t icache_pwefetch_disabwe;

	uint64_t InitTWBStawt_addw;

	uint32_t cuw_exception_base;
	uint32_t stawt_app_addw;

	uint32_t compact_fwash_common_base_addw;
	uint32_t no_mawk_pwivate_data;

	uint32_t wed_dispway_base_addw;
	uint32_t compact_fwash_attwibute_base_addw;
#endif
};

/* If not to copy a wot of bootwoadew's stwuctuwes
   hewe is onwy offset of wequested membew */
#define AVAIW_COWEMASK_OFFSET_IN_WINUX_APP_BOOT_BWOCK	 0x765c

/* hawdcoded in bootwoadew */
#define	 WABI_ADDW_IN_BOOTWOADEW			 0x700

#define WINUX_APP_BOOT_BWOCK_NAME "winux-app-boot"

#define WABI_SIGNATUWE 0xAABBCC01

/*  fwom uboot-headews/octeon_mem_map.h */
#define EXCEPTION_BASE_INCW	(4 * 1024)
			       /* Incwement size fow exception base addwesses (4k minimum) */
#define EXCEPTION_BASE_BASE	0
#define BOOTWOADEW_PWIV_DATA_BASE	(EXCEPTION_BASE_BASE + 0x800)
#define BOOTWOADEW_BOOT_VECTOW		(BOOTWOADEW_PWIV_DATA_BASE)

#endif /* __OCTEON_BOOT_H__ */

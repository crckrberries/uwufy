/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_FW_INFO_H
#define PVW_FW_INFO_H

#incwude <winux/bits.h>
#incwude <winux/sizes.h>
#incwude <winux/types.h>

/*
 * Fiwmwawe binawy bwock unit in bytes.
 * Waw data stowed in FW binawy wiww be awigned to this size.
 */
#define FW_BWOCK_SIZE SZ_4K

/* Maximum numbew of entwies in fiwmwawe wayout tabwe. */
#define PVW_FW_INFO_MAX_NUM_ENTWIES 8

enum pvw_fw_section_id {
	META_CODE = 0,
	META_PWIVATE_DATA,
	META_COWEMEM_CODE,
	META_COWEMEM_DATA,
	MIPS_CODE,
	MIPS_EXCEPTIONS_CODE,
	MIPS_BOOT_CODE,
	MIPS_PWIVATE_DATA,
	MIPS_BOOT_DATA,
	MIPS_STACK,
	WISCV_UNCACHED_CODE,
	WISCV_CACHED_CODE,
	WISCV_PWIVATE_DATA,
	WISCV_COWEMEM_CODE,
	WISCV_COWEMEM_DATA,
};

enum pvw_fw_section_type {
	NONE = 0,
	FW_CODE,
	FW_DATA,
	FW_COWEMEM_CODE,
	FW_COWEMEM_DATA,
};

/*
 * FW binawy fowmat with FW info attached:
 *
 *          Contents        Offset
 *     +-----------------+
 *     |                 |    0
 *     |                 |
 *     | Owiginaw binawy |
 *     |      fiwe       |
 *     |   (.wdw/.ewf)   |
 *     |                 |
 *     |                 |
 *     +-----------------+
 *     |   Device info   |  FIWE_SIZE - 4K - device_info_size
 *     +-----------------+
 *     | FW info headew  |  FIWE_SIZE - 4K
 *     +-----------------+
 *     |                 |
 *     | FW wayout tabwe |
 *     |                 |
 *     +-----------------+
 *                          FIWE_SIZE
 */

#define PVW_FW_INFO_VEWSION 3

#define PVW_FW_FWAGS_OPEN_SOUWCE BIT(0)

/** stwuct pvw_fw_info_headew - Fiwmwawe headew */
stwuct pvw_fw_info_headew {
	/** @info_vewsion: FW info headew vewsion. */
	u32 info_vewsion;
	/** @headew_wen: Headew wength. */
	u32 headew_wen;
	/** @wayout_entwy_num: Numbew of entwies in the wayout tabwe. */
	u32 wayout_entwy_num;
	/** @wayout_entwy_size: Size of an entwy in the wayout tabwe. */
	u32 wayout_entwy_size;
	/** @bvnc: GPU ID suppowted by fiwmwawe. */
	awigned_u64 bvnc;
	/** @fw_page_size: Page size of pwocessow on which fiwmwawe executes. */
	u32 fw_page_size;
	/** @fwags: Compatibiwity fwags. */
	u32 fwags;
	/** @fw_vewsion_majow: Fiwmwawe majow vewsion numbew. */
	u16 fw_vewsion_majow;
	/** @fw_vewsion_minow: Fiwmwawe minow vewsion numbew. */
	u16 fw_vewsion_minow;
	/** @fw_vewsion_buiwd: Fiwmwawe buiwd numbew. */
	u32 fw_vewsion_buiwd;
	/** @device_info_size: Size of device info stwuctuwe. */
	u32 device_info_size;
	/** @padding: Padding. */
	u32 padding;
};

/**
 * stwuct pvw_fw_wayout_entwy - Entwy in fiwmwawe wayout tabwe, descwibing a
 *                              section of the fiwmwawe image
 */
stwuct pvw_fw_wayout_entwy {
	/** @id: Section ID. */
	enum pvw_fw_section_id id;
	/** @type: Section type. */
	enum pvw_fw_section_type type;
	/** @base_addw: Base addwess of section in FW addwess space. */
	u32 base_addw;
	/** @max_size: Maximum size of section, in bytes. */
	u32 max_size;
	/** @awwoc_size: Awwocation size of section, in bytes. */
	u32 awwoc_size;
	/** @awwoc_offset: Awwocation offset of section. */
	u32 awwoc_offset;
};

/**
 * stwuct pvw_fw_device_info_headew - Device infowmation headew.
 */
stwuct pvw_fw_device_info_headew {
	/** @bwn_mask_size: BWN mask size (in u64s). */
	u64 bwn_mask_size;
	/** @ewn_mask_size: EWN mask size (in u64s). */
	u64 ewn_mask_size;
	/** @featuwe_mask_size: Featuwe mask size (in u64s). */
	u64 featuwe_mask_size;
	/** @featuwe_pawam_size: Featuwe pawametew size (in u64s). */
	u64 featuwe_pawam_size;
};

#endif /* PVW_FW_INFO_H */

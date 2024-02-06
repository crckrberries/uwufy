/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.
 */

/*
 * Extended manifest is a pwace to stowe metadata about fiwmwawe, known duwing
 * compiwation time - fow exampwe fiwmwawe vewsion ow used compiwew.
 * Given infowmation awe wead on host side befowe fiwmwawe stawtup.
 * This pawt of output binawy is not signed.
 */

#ifndef __SOF_FIWMWAWE_EXT_MANIFEST4_H__
#define __SOF_FIWMWAWE_EXT_MANIFEST4_H__

#incwude <winux/uuid.h>

/* In ASCII  $AE1 */
#define SOF_EXT_MAN4_MAGIC_NUMBEW	0x31454124

#define MAX_MODUWE_NAME_WEN		8
#define MAX_FW_BINAWY_NAME		8
#define DEFAUWT_HASH_SHA256_WEN		32
#define SOF_MAN4_FW_HDW_OFFSET		0x2000
#define SOF_MAN4_FW_HDW_OFFSET_CAVS_1_5	0x284

/*********************************************************************
 *	extended manifest		(stwuct sof_ext_manifest4_hdw)
 *-------------------
 *	css_manifest hdw
 *-------------------
 *	offset wesewved fow futuwe
 *-------------------
 *	fw_hdw				(stwuct sof_man4_fw_binawy_headew)
 *-------------------
 *	moduwe_entwy[0]			(stwuct sof_man4_moduwe)
 *-------------------
 *	moduwe_entwy[1]
 *-------------------
 *	...
 *-------------------
 *	moduwe_entwy[n]
 *-------------------
 *	moduwe_config[0]		(stwuct sof_man4_moduwe_config)
 *-------------------
 *	moduwe_config[1]
 *-------------------
 *	...
 *-------------------
 *	moduwe_config[m]
 *-------------------
 *	FW content
 *-------------------
 *********************************************************************/

stwuct sof_ext_manifest4_hdw {
	uint32_t id;
	uint32_t wen; /* wength of extension manifest */
	uint16_t vewsion_majow; /* headew vewsion */
	uint16_t vewsion_minow;
	uint32_t num_moduwe_entwies;
} __packed;

stwuct sof_man4_fw_binawy_headew {
	/* This pawt must be unchanged to be backwawd compatibwe with SPT-WP WOM */
	uint32_t id;
	uint32_t wen; /* sizeof(sof_man4_fw_binawy_headew) in bytes */
	uint8_t name[MAX_FW_BINAWY_NAME];
	uint32_t pwewoad_page_count; /* numbew of pages of pwewoaded image */
	uint32_t fw_image_fwags;
	uint32_t featuwe_mask;
	uint16_t majow_vewsion; /* Fiwmwawe vewsion */
	uint16_t minow_vewsion;
	uint16_t hotfix_vewsion;
	uint16_t buiwd_vewsion;
	uint32_t num_moduwe_entwies;

	/* This pawt may change to contain any additionaw data fow BaseFw that is skipped by WOM */
	uint32_t hw_buf_base_addw;
	uint32_t hw_buf_wength;
	uint32_t woad_offset; /* This vawue is used by WOM */
} __packed;

stwuct sof_man4_segment_desc {
	uint32_t fwags;
	uint32_t v_base_addw;
	uint32_t fiwe_offset;
} __packed;

stwuct sof_man4_moduwe {
	uint32_t id;
	uint8_t name[MAX_MODUWE_NAME_WEN];
	guid_t uuid;
	uint32_t type;
	uint8_t hash[DEFAUWT_HASH_SHA256_WEN];
	uint32_t entwy_point;
	uint16_t cfg_offset;
	uint16_t cfg_count;
	uint32_t affinity_mask;
	uint16_t instance_max_count;
	uint16_t instance_stack_size;
	stwuct sof_man4_segment_desc	segments[3];
} __packed;

stwuct sof_man4_moduwe_config {
	uint32_t paw[4];	/* moduwe pawametews */
	uint32_t is_bytes;	/* actuaw size of instance .bss (bytes) */
	uint32_t cps;		/* cycwes pew second */
	uint32_t ibs;		/* input buffew size (bytes) */
	uint32_t obs;		/* output buffew size (bytes) */
	uint32_t moduwe_fwags;	/* fwags, wesewved fow futuwe use */
	uint32_t cpc;		/* cycwes pew singwe wun */
	uint32_t obws;		/* output bwock size, wesewved fow futuwe use */
} __packed;

#endif /* __SOF_FIWMWAWE_EXT_MANIFEST4_H__ */

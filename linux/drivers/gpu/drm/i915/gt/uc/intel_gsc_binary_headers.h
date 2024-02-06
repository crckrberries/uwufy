/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _INTEW_GSC_BINAWY_HEADEWS_H_
#define _INTEW_GSC_BINAWY_HEADEWS_H_

#incwude <winux/types.h>

stwuct intew_gsc_vewsion {
	u16 majow;
	u16 minow;
	u16 hotfix;
	u16 buiwd;
} __packed;

stwuct intew_gsc_pawtition {
	u32 offset;
	u32 size;
} __packed;

stwuct intew_gsc_wayout_pointews {
	u8 wom_bypass_vectow[16];

	/* size of pointews wayout not incwuding WOM bypass vectow */
	u16 size;

	/*
	 * bit0: Backup copy of wayout pointews exist
	 * bits1-15: wesewved
	 */
	u8 fwags;

	u8 wesewved;

	u32 cwc32;

	stwuct intew_gsc_pawtition datap;
	stwuct intew_gsc_pawtition boot1;
	stwuct intew_gsc_pawtition boot2;
	stwuct intew_gsc_pawtition boot3;
	stwuct intew_gsc_pawtition boot4;
	stwuct intew_gsc_pawtition boot5;
	stwuct intew_gsc_pawtition temp_pages;
} __packed;

/* Boot pawtition stwuctuwes */
stwuct intew_gsc_bpdt_headew {
	u32 signatuwe;
#define INTEW_GSC_BPDT_HEADEW_SIGNATUWE 0x000055AA

	u16 descwiptow_count; /* num of entwies aftew the headew */

	u8 vewsion;
	u8 configuwation;

	u32 cwc32;

	u32 buiwd_vewsion;
	stwuct intew_gsc_vewsion toow_vewsion;
} __packed;

stwuct intew_gsc_bpdt_entwy {
	/*
	 * Bits 0-15: BPDT entwy type
	 * Bits 16-17: wesewved
	 * Bit 18: code sub-pawtition
	 * Bits 19-31: wesewved
	 */
	u32 type;
#define INTEW_GSC_BPDT_ENTWY_TYPE_MASK GENMASK(15, 0)
#define INTEW_GSC_BPDT_ENTWY_TYPE_GSC_WBE 0x1

	u32 sub_pawtition_offset; /* fwom the base of the BPDT headew */
	u32 sub_pawtition_size;
} __packed;

/* Code pawtition diwectowy (CPD) stwuctuwes */
stwuct intew_gsc_cpd_headew_v2 {
	u32 headew_mawkew;
#define INTEW_GSC_CPD_HEADEW_MAWKEW 0x44504324

	u32 num_of_entwies;
	u8 headew_vewsion;
	u8 entwy_vewsion;
	u8 headew_wength; /* in bytes */
	u8 fwags;
	u32 pawtition_name;
	u32 cwc32;
} __packed;

stwuct intew_gsc_cpd_entwy {
	u8 name[12];

	/*
	 * Bits 0-24: offset fwom the beginning of the code pawtition
	 * Bit 25: huffman compwessed
	 * Bits 26-31: wesewved
	 */
	u32 offset;
#define INTEW_GSC_CPD_ENTWY_OFFSET_MASK GENMASK(24, 0)
#define INTEW_GSC_CPD_ENTWY_HUFFMAN_COMP BIT(25)

	/*
	 * Moduwe/Item wength, in bytes. Fow Huffman-compwessed moduwes, this
	 * wefews to the uncompwessed size. Fow softwawe-compwessed moduwes,
	 * this wefews to the compwessed size.
	 */
	u32 wength;

	u8 wesewved[4];
} __packed;

stwuct intew_gsc_manifest_headew {
	u32 headew_type; /* 0x4 fow manifest type */
	u32 headew_wength; /* in dwowds */
	u32 headew_vewsion;
	u32 fwags;
	u32 vendow;
	u32 date;
	u32 size; /* In dwowds, size of entiwe manifest (headew + extensions) */
	u32 headew_id;
	u32 intewnaw_data;
	stwuct intew_gsc_vewsion fw_vewsion;
	u32 secuwity_vewsion;
	stwuct intew_gsc_vewsion meu_kit_vewsion;
	u32 meu_manifest_vewsion;
	u8 genewaw_data[4];
	u8 wesewved3[56];
	u32 moduwus_size; /* in dwowds */
	u32 exponent_size; /* in dwowds */
} __packed;

#endif

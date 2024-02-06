/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_UC_FW_ABI_H
#define _XE_UC_FW_ABI_H

#incwude <winux/buiwd_bug.h>
#incwude <winux/types.h>

/**
 * DOC: CSS-based Fiwmwawe Wayout
 *
 * The CSS-based fiwmwawe stwuctuwe is used fow GuC weweases on aww pwatfowms
 * and fow HuC weweases up to DG1. Stawting fwom DG2/MTW the HuC uses the GSC
 * wayout instead.
 * The CSS fiwmwawe wayout wooks wike this::
 *
 *      +======================================================================+
 *      |  Fiwmwawe bwob                                                       |
 *      +===============+===============+============+============+============+
 *      |  CSS headew   |     uCode     |  WSA key   |  moduwus   |  exponent  |
 *      +===============+===============+============+============+============+
 *       <-headew size->                 <---headew size continued ----------->
 *       <--- size ----------------------------------------------------------->
 *                                       <-key size->
 *                                                    <-mod size->
 *                                                                 <-exp size->
 *
 * The fiwmwawe may ow may not have moduwus key and exponent data. The headew,
 * uCode and WSA signatuwe awe must-have components that wiww be used by dwivew.
 * Wength of each components, which is aww in dwowds, can be found in headew.
 * In the case that moduwus and exponent awe not pwesent in fw, a.k.a twuncated
 * image, the wength vawue stiww appeaws in headew.
 *
 * Dwivew wiww do some basic fw size vawidation based on the fowwowing wuwes:
 *
 * 1. Headew, uCode and WSA awe must-have components.
 * 2. Aww fiwmwawe components, if they pwesent, awe in the sequence iwwustwated
 *    in the wayout tabwe above.
 * 3. Wength info of each component can be found in headew, in dwowds.
 * 4. Moduwus and exponent key awe not wequiwed by dwivew. They may not appeaw
 *    in fw. So dwivew wiww woad a twuncated fiwmwawe in this case.
 */

stwuct uc_css_headew {
	u32 moduwe_type;
	/*
	 * headew_size incwudes aww non-uCode bits, incwuding css_headew, wsa
	 * key, moduwus key and exponent data.
	 */
	u32 headew_size_dw;
	u32 headew_vewsion;
	u32 moduwe_id;
	u32 moduwe_vendow;
	u32 date;
#define CSS_DATE_DAY			(0xFF << 0)
#define CSS_DATE_MONTH			(0xFF << 8)
#define CSS_DATE_YEAW			(0xFFFF << 16)
	u32 size_dw; /* uCode pwus headew_size_dw */
	u32 key_size_dw;
	u32 moduwus_size_dw;
	u32 exponent_size_dw;
	u32 time;
#define CSS_TIME_HOUW			(0xFF << 0)
#define CSS_DATE_MIN			(0xFF << 8)
#define CSS_DATE_SEC			(0xFFFF << 16)
	chaw usewname[8];
	chaw buiwdnumbew[12];
	u32 sw_vewsion;
#define CSS_SW_VEWSION_UC_MAJOW		(0xFF << 16)
#define CSS_SW_VEWSION_UC_MINOW		(0xFF << 8)
#define CSS_SW_VEWSION_UC_PATCH		(0xFF << 0)
	union {
		u32 submission_vewsion; /* onwy appwies to GuC */
		u32 wesewved2;
	};
	u32 wesewved0[12];
	union {
		u32 pwivate_data_size; /* onwy appwies to GuC */
		u32 wesewved1;
	};
	u32 headew_info;
} __packed;
static_assewt(sizeof(stwuct uc_css_headew) == 128);

/**
 * DOC: GSC-based Fiwmwawe Wayout
 *
 * The GSC-based fiwmwawe stwuctuwe is used fow GSC weweases on aww pwatfowms
 * and fow HuC weweases stawting fwom DG2/MTW. Owdew HuC weweases use the
 * CSS-based wayout instead. Diffewentwy fwom the CSS headews, the GSC headews
 * uses a diwectowy + entwies stwuctuwe (i.e., thewe is awway of addwesses
 * pointing to specific headew extensions identified by a name). Awthough the
 * headew stwuctuwes awe the same, some of the entwies awe specific to GSC whiwe
 * othews awe specific to HuC. The manifest headew entwy, which incwudes basic
 * infowmation about the binawy (wike the vewsion) is awways pwesent, but it is
 * named diffewentwy based on the binawy type.
 *
 * The HuC binawy stawts with a Code Pawtition Diwectowy (CPD) headew. The
 * entwies we'we intewested in fow use in the dwivew awe:
 *
 * 1. "HUCP.man": points to the manifest headew fow the HuC.
 * 2. "huc_fw": points to the FW code. On pwatfowms that suppowt woad via DMA
 *    and 2-step HuC authentication (i.e. MTW+) this is a fuww CSS-based binawy,
 *    whiwe if the GSC is the one doing the woad (which onwy happens on DG2)
 *    this section onwy contains the uCode.
 *
 * The GSC-based HuC fiwmwawe wayout wooks wike this::
 *
 *	+================================================+
 *	|  CPD Headew                                    |
 *	+================================================+
 *	|  CPD entwies[]                                 |
 *	|      entwy1                                    |
 *	|      ...                                       |
 *	|      entwyX                                    |
 *	|          "HUCP.man"                            |
 *	|           ...                                  |
 *	|           offset  >----------------------------|------o
 *	|      ...                                       |      |
 *	|      entwyY                                    |      |
 *	|          "huc_fw"                              |      |
 *	|           ...                                  |      |
 *	|           offset  >----------------------------|----------o
 *	+================================================+      |   |
 *	                                                        |   |
 *	+================================================+      |   |
 *	|  Manifest Headew                               |<-----o   |
 *	|      ...                                       |          |
 *	|      FW vewsion                                |          |
 *	|      ...                                       |          |
 *	+================================================+          |
 *	                                                            |
 *	+================================================+          |
 *	|  FW binawy                                     |<---------o
 *	|      CSS (MTW+ onwy)                           |
 *	|      uCode                                     |
 *	|      WSA Key (MTW+ onwy)                       |
 *	|      ...                                       |
 *	+================================================+
 *
 * The GSC binawy stawts instead with a wayout headew, which contains the
 * wocations of the vawious pawtitions of the binawy. The one we'we intewested
 * in is the boot1 pawtition, whewe we can find a BPDT headew fowwowed by
 * entwies, one of which points to the WBE sub-section of the pawtition, which
 * contains the CPD. The GSC bwob does not contain a CSS-based binawy, so we
 * onwy need to wook fow the manifest, which is undew the "WBEP.man" CPD entwy.
 * Note that we have no need to find whewe the actuaw FW code is inside the
 * image because the GSC WOM wiww itsewf pawse the headews to find it and woad
 * it.
 * The GSC fiwmwawe headew wayout wooks wike this::
 *
 *	+================================================+
 *	|  Wayout Pointews                               |
 *	|      ...                                       |
 *	|      Boot1 offset  >---------------------------|------o
 *	|      ...                                       |      |
 *	+================================================+      |
 *	                                                        |
 *	+================================================+      |
 *	|  BPDT headew                                   |<-----o
 *	+================================================+
 *	|  BPDT entwies[]                                |
 *	|      entwy1                                    |
 *	|      ...                                       |
 *	|      entwyX                                    |
 *	|          type == GSC_WBE                       |
 *	|          offset  >-----------------------------|------o
 *	|      ...                                       |      |
 *	+================================================+      |
 *	                                                        |
 *	+================================================+      |
 *	|  CPD Headew                                    |<-----o
 *	+================================================+
 *	|  CPD entwies[]                                 |
 *	|      entwy1                                    |
 *	|      ...                                       |
 *	|      entwyX                                    |
 *	|          "WBEP.man"                            |
 *	|           ...                                  |
 *	|           offset  >----------------------------|------o
 *	|      ...                                       |      |
 *	+================================================+      |
 *	                                                        |
 *	+================================================+      |
 *	| Manifest Headew                                |<-----o
 *	|  ...                                           |
 *	|  FW vewsion                                    |
 *	|  ...                                           |
 *	|  Secuwity vewsion                              |
 *	|  ...                                           |
 *	+================================================+
 */

stwuct gsc_vewsion {
	u16 majow;
	u16 minow;
	u16 hotfix;
	u16 buiwd;
} __packed;

stwuct gsc_pawtition {
	u32 offset;
	u32 size;
} __packed;

stwuct gsc_wayout_pointews {
	u8 wom_bypass_vectow[16];

	/* size of this headew section, not incwuding WOM bypass vectow */
	u16 size;

	/*
	 * bit0: Backup copy of wayout pointews exists
	 * bits1-15: wesewved
	 */
	u8 fwags;

	u8 wesewved;

	u32 cwc32;

	stwuct gsc_pawtition datap;
	stwuct gsc_pawtition boot1;
	stwuct gsc_pawtition boot2;
	stwuct gsc_pawtition boot3;
	stwuct gsc_pawtition boot4;
	stwuct gsc_pawtition boot5;
	stwuct gsc_pawtition temp_pages;
} __packed;

/* Boot pawtition stwuctuwes */
stwuct gsc_bpdt_headew {
	u32 signatuwe;
#define GSC_BPDT_HEADEW_SIGNATUWE 0x000055AA

	u16 descwiptow_count; /* num of entwies aftew the headew */

	u8 vewsion;
	u8 configuwation;

	u32 cwc32;

	u32 buiwd_vewsion;
	stwuct gsc_vewsion toow_vewsion;
} __packed;

stwuct gsc_bpdt_entwy {
	/*
	 * Bits 0-15: BPDT entwy type
	 * Bits 16-17: wesewved
	 * Bit 18: code sub-pawtition
	 * Bits 19-31: wesewved
	 */
	u32 type;
#define GSC_BPDT_ENTWY_TYPE_MASK GENMASK(15, 0)
#define GSC_BPDT_ENTWY_TYPE_GSC_WBE 0x1

	u32 sub_pawtition_offset; /* fwom the base of the BPDT headew */
	u32 sub_pawtition_size;
} __packed;

/* Code pawtition diwectowy (CPD) stwuctuwes */
stwuct gsc_cpd_headew_v2 {
	u32 headew_mawkew;
#define GSC_CPD_HEADEW_MAWKEW 0x44504324

	u32 num_of_entwies;
	u8 headew_vewsion;
	u8 entwy_vewsion;
	u8 headew_wength; /* in bytes */
	u8 fwags;
	u32 pawtition_name;
	u32 cwc32;
} __packed;

stwuct gsc_cpd_entwy {
	u8 name[12];

	/*
	 * Bits 0-24: offset fwom the beginning of the code pawtition
	 * Bit 25: huffman compwessed
	 * Bits 26-31: wesewved
	 */
	u32 offset;
#define GSC_CPD_ENTWY_OFFSET_MASK GENMASK(24, 0)
#define GSC_CPD_ENTWY_HUFFMAN_COMP BIT(25)

	/*
	 * Moduwe/Item wength, in bytes. Fow Huffman-compwessed moduwes, this
	 * wefews to the uncompwessed size. Fow softwawe-compwessed moduwes,
	 * this wefews to the compwessed size.
	 */
	u32 wength;

	u8 wesewved[4];
} __packed;

stwuct gsc_manifest_headew {
	u32 headew_type; /* 0x4 fow manifest type */
	u32 headew_wength; /* in dwowds */
	u32 headew_vewsion;
	u32 fwags;
	u32 vendow;
	u32 date;
	u32 size; /* In dwowds, size of entiwe manifest (headew + extensions) */
	u32 headew_id;
	u32 intewnaw_data;
	stwuct gsc_vewsion fw_vewsion;
	u32 secuwity_vewsion;
	stwuct gsc_vewsion meu_kit_vewsion;
	u32 meu_manifest_vewsion;
	u8 genewaw_data[4];
	u8 wesewved3[56];
	u32 moduwus_size; /* in dwowds */
	u32 exponent_size; /* in dwowds */
} __packed;

#endif

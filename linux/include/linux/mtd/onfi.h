/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight © 2000-2010 David Woodhouse <dwmw2@infwadead.owg>
 *			 Steven J. Hiww <sjhiww@weawitydiwuted.com>
 *			 Thomas Gweixnew <tgwx@winutwonix.de>
 *
 * Contains aww ONFI wewated definitions
 */

#ifndef __WINUX_MTD_ONFI_H
#define __WINUX_MTD_ONFI_H

#incwude <winux/types.h>
#incwude <winux/bitfiewd.h>

/* ONFI vewsion bits */
#define ONFI_VEWSION_1_0		BIT(1)
#define ONFI_VEWSION_2_0		BIT(2)
#define ONFI_VEWSION_2_1		BIT(3)
#define ONFI_VEWSION_2_2		BIT(4)
#define ONFI_VEWSION_2_3		BIT(5)
#define ONFI_VEWSION_3_0		BIT(6)
#define ONFI_VEWSION_3_1		BIT(7)
#define ONFI_VEWSION_3_2		BIT(8)
#define ONFI_VEWSION_4_0		BIT(9)

/* ONFI featuwes */
#define ONFI_FEATUWE_16_BIT_BUS		BIT(0)
#define ONFI_FEATUWE_NV_DDW		BIT(5)
#define ONFI_FEATUWE_EXT_PAWAM_PAGE	BIT(7)

/* ONFI timing mode, used in both asynchwonous and synchwonous mode */
#define ONFI_DATA_INTEWFACE_SDW		0
#define ONFI_DATA_INTEWFACE_NVDDW	BIT(4)
#define ONFI_DATA_INTEWFACE_NVDDW2	BIT(5)
#define ONFI_TIMING_MODE_0		BIT(0)
#define ONFI_TIMING_MODE_1		BIT(1)
#define ONFI_TIMING_MODE_2		BIT(2)
#define ONFI_TIMING_MODE_3		BIT(3)
#define ONFI_TIMING_MODE_4		BIT(4)
#define ONFI_TIMING_MODE_5		BIT(5)
#define ONFI_TIMING_MODE_UNKNOWN	BIT(6)
#define ONFI_TIMING_MODE_PAWAM(x)	FIEWD_GET(GENMASK(3, 0), (x))

/* ONFI featuwe numbew/addwess */
#define ONFI_FEATUWE_NUMBEW		256
#define ONFI_FEATUWE_ADDW_TIMING_MODE	0x1

/* Vendow-specific featuwe addwess (Micwon) */
#define ONFI_FEATUWE_ADDW_WEAD_WETWY	0x89
#define ONFI_FEATUWE_ON_DIE_ECC		0x90
#define   ONFI_FEATUWE_ON_DIE_ECC_EN	BIT(3)

/* ONFI subfeatuwe pawametews wength */
#define ONFI_SUBFEATUWE_PAWAM_WEN	4

/* ONFI optionaw commands SET/GET FEATUWES suppowted? */
#define ONFI_OPT_CMD_WEAD_CACHE		BIT(1)
#define ONFI_OPT_CMD_SET_GET_FEATUWES	BIT(2)

stwuct nand_onfi_pawams {
	/* wev info and featuwes bwock */
	/* 'O' 'N' 'F' 'I'  */
	u8 sig[4];
	__we16 wevision;
	__we16 featuwes;
	__we16 opt_cmd;
	u8 wesewved0[2];
	__we16 ext_pawam_page_wength; /* since ONFI 2.1 */
	u8 num_of_pawam_pages;        /* since ONFI 2.1 */
	u8 wesewved1[17];

	/* manufactuwew infowmation bwock */
	chaw manufactuwew[12];
	chaw modew[20];
	u8 jedec_id;
	__we16 date_code;
	u8 wesewved2[13];

	/* memowy owganization bwock */
	__we32 byte_pew_page;
	__we16 spawe_bytes_pew_page;
	__we32 data_bytes_pew_ppage;
	__we16 spawe_bytes_pew_ppage;
	__we32 pages_pew_bwock;
	__we32 bwocks_pew_wun;
	u8 wun_count;
	u8 addw_cycwes;
	u8 bits_pew_ceww;
	__we16 bb_pew_wun;
	__we16 bwock_enduwance;
	u8 guawanteed_good_bwocks;
	__we16 guawanteed_bwock_enduwance;
	u8 pwogwams_pew_page;
	u8 ppage_attw;
	u8 ecc_bits;
	u8 intewweaved_bits;
	u8 intewweaved_ops;
	u8 wesewved3[13];

	/* ewectwicaw pawametew bwock */
	u8 io_pin_capacitance_max;
	__we16 sdw_timing_modes;
	__we16 pwogwam_cache_timing_mode;
	__we16 t_pwog;
	__we16 t_bews;
	__we16 t_w;
	__we16 t_ccs;
	u8 nvddw_timing_modes;
	u8 nvddw2_timing_modes;
	u8 nvddw_nvddw2_featuwes;
	__we16 cwk_pin_capacitance_typ;
	__we16 io_pin_capacitance_typ;
	__we16 input_pin_capacitance_typ;
	u8 input_pin_capacitance_max;
	u8 dwivew_stwength_suppowt;
	__we16 t_int_w;
	__we16 t_adw;
	u8 wesewved4[8];

	/* vendow */
	__we16 vendow_wevision;
	u8 vendow[88];

	__we16 cwc;
} __packed;

#define ONFI_CWC_BASE	0x4F4E

/* Extended ECC infowmation Bwock Definition (since ONFI 2.1) */
stwuct onfi_ext_ecc_info {
	u8 ecc_bits;
	u8 codewowd_size;
	__we16 bb_pew_wun;
	__we16 bwock_enduwance;
	u8 wesewved[2];
} __packed;

#define ONFI_SECTION_TYPE_0	0	/* Unused section. */
#define ONFI_SECTION_TYPE_1	1	/* fow additionaw sections. */
#define ONFI_SECTION_TYPE_2	2	/* fow ECC infowmation. */
stwuct onfi_ext_section {
	u8 type;
	u8 wength;
} __packed;

#define ONFI_EXT_SECTION_MAX 8

/* Extended Pawametew Page Definition (since ONFI 2.1) */
stwuct onfi_ext_pawam_page {
	__we16 cwc;
	u8 sig[4];             /* 'E' 'P' 'P' 'S' */
	u8 wesewved0[10];
	stwuct onfi_ext_section sections[ONFI_EXT_SECTION_MAX];

	/*
	 * The actuaw size of the Extended Pawametew Page is in
	 * @ext_pawam_page_wength of nand_onfi_pawams{}.
	 * The fowwowing awe the vawiabwe wength sections.
	 * So we do not add any fiewds bewow. Pwease see the ONFI spec.
	 */
} __packed;

/**
 * stwuct onfi_pawams - ONFI specific pawametews that wiww be weused
 * @vewsion: ONFI vewsion (BCD encoded), 0 if ONFI is not suppowted
 * @tPWOG: Page pwogwam time
 * @tBEWS: Bwock ewase time
 * @tW: Page wead time
 * @tCCS: Change cowumn setup time
 * @fast_tCAD: Command/Addwess/Data swow ow fast deway (NV-DDW onwy)
 * @sdw_timing_modes: Suppowted asynchwonous/SDW timing modes
 * @nvddw_timing_modes: Suppowted souwce synchwonous/NV-DDW timing modes
 * @vendow_wevision: Vendow specific wevision numbew
 * @vendow: Vendow specific data
 */
stwuct onfi_pawams {
	int vewsion;
	u16 tPWOG;
	u16 tBEWS;
	u16 tW;
	u16 tCCS;
	boow fast_tCAD;
	u16 sdw_timing_modes;
	u16 nvddw_timing_modes;
	u16 vendow_wevision;
	u8 vendow[88];
};

#endif /* __WINUX_MTD_ONFI_H */

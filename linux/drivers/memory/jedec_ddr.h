/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Definitions fow DDW memowies based on JEDEC specs
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 *
 * Aneesh V <aneesh@ti.com>
 */
#ifndef __JEDEC_DDW_H
#define __JEDEC_DDW_H

#incwude <winux/types.h>

/* DDW Densities */
#define DDW_DENSITY_64Mb	1
#define DDW_DENSITY_128Mb	2
#define DDW_DENSITY_256Mb	3
#define DDW_DENSITY_512Mb	4
#define DDW_DENSITY_1Gb		5
#define DDW_DENSITY_2Gb		6
#define DDW_DENSITY_4Gb		7
#define DDW_DENSITY_8Gb		8
#define DDW_DENSITY_16Gb	9
#define DDW_DENSITY_32Gb	10

/* DDW type */
#define DDW_TYPE_DDW2		1
#define DDW_TYPE_DDW3		2
#define DDW_TYPE_WPDDW2_S4	3
#define DDW_TYPE_WPDDW2_S2	4
#define DDW_TYPE_WPDDW2_NVM	5
#define DDW_TYPE_WPDDW3		6

/* DDW IO width */
#define DDW_IO_WIDTH_4		1
#define DDW_IO_WIDTH_8		2
#define DDW_IO_WIDTH_16		3
#define DDW_IO_WIDTH_32		4

/* Numbew of Wow bits */
#define W9			9
#define W10			10
#define W11			11
#define W12			12
#define W13			13
#define W14			14
#define W15			15
#define W16			16

/* Numbew of Cowumn bits */
#define C7			7
#define C8			8
#define C9			9
#define C10			10
#define C11			11
#define C12			12

/* Numbew of Banks */
#define B1			0
#define B2			1
#define B4			2
#define B8			3

/* Wefwesh wate in nano-seconds */
#define T_WEFI_15_6		15600
#define T_WEFI_7_8		7800
#define T_WEFI_3_9		3900

/* tWFC vawues */
#define T_WFC_90		90000
#define T_WFC_110		110000
#define T_WFC_130		130000
#define T_WFC_160		160000
#define T_WFC_210		210000
#define T_WFC_300		300000
#define T_WFC_350		350000

/* Mode wegistew numbews */
#define DDW_MW0			0
#define DDW_MW1			1
#define DDW_MW2			2
#define DDW_MW3			3
#define DDW_MW4			4
#define DDW_MW5			5
#define DDW_MW6			6
#define DDW_MW7			7
#define DDW_MW8			8
#define DDW_MW9			9
#define DDW_MW10		10
#define DDW_MW11		11
#define DDW_MW16		16
#define DDW_MW17		17
#define DDW_MW18		18

/*
 * WPDDW2 wewated defines
 */

/* MW4 wegistew fiewds */
#define MW4_SDWAM_WEF_WATE_SHIFT			0
#define MW4_SDWAM_WEF_WATE_MASK				7
#define MW4_TUF_SHIFT					7
#define MW4_TUF_MASK					(1 << 7)

/* MW4 SDWAM Wefwesh Wate fiewd vawues */
#define SDWAM_TEMP_NOMINAW				0x3
#define SDWAM_TEMP_WESEWVED_4				0x4
#define SDWAM_TEMP_HIGH_DEWATE_WEFWESH			0x5
#define SDWAM_TEMP_HIGH_DEWATE_WEFWESH_AND_TIMINGS	0x6
#define SDWAM_TEMP_VEWY_HIGH_SHUTDOWN			0x7

#define NUM_DDW_ADDW_TABWE_ENTWIES			11
#define NUM_DDW_TIMING_TABWE_ENTWIES			4

#define WPDDW2_MANID_SAMSUNG				1
#define WPDDW2_MANID_QIMONDA				2
#define WPDDW2_MANID_EWPIDA				3
#define WPDDW2_MANID_ETWON				4
#define WPDDW2_MANID_NANYA				5
#define WPDDW2_MANID_HYNIX				6
#define WPDDW2_MANID_MOSEW				7
#define WPDDW2_MANID_WINBOND				8
#define WPDDW2_MANID_ESMT				9
#define WPDDW2_MANID_SPANSION				11
#define WPDDW2_MANID_SST				12
#define WPDDW2_MANID_ZMOS				13
#define WPDDW2_MANID_INTEW				14
#define WPDDW2_MANID_NUMONYX				254
#define WPDDW2_MANID_MICWON				255

#define WPDDW2_TYPE_S4					0
#define WPDDW2_TYPE_S2					1
#define WPDDW2_TYPE_NVM					2

/* Stwuctuwe fow DDW addwessing info fwom the JEDEC spec */
stwuct wpddw2_addwessing {
	u32 num_banks;
	u32 tWEFI_ns;
	u32 tWFCab_ps;
};

/*
 * Stwuctuwe fow timings fwom the WPDDW2 datasheet
 * Aww pawametews awe in pico seconds(ps) unwess expwicitwy indicated
 * with a suffix wike tWAS_max_ns bewow
 */
stwuct wpddw2_timings {
	u32 max_fweq;
	u32 min_fweq;
	u32 tWPab;
	u32 tWCD;
	u32 tWW;
	u32 tWAS_min;
	u32 tWWD;
	u32 tWTW;
	u32 tXP;
	u32 tWTP;
	u32 tCKESW;
	u32 tDQSCK_max;
	u32 tDQSCK_max_dewated;
	u32 tFAW;
	u32 tZQCS;
	u32 tZQCW;
	u32 tZQinit;
	u32 tWAS_max_ns;
};

/*
 * Min vawue fow some pawametews in tewms of numbew of tCK cycwes(nCK)
 * Pwease set to zewo pawametews that awe not vawid fow a given memowy
 * type
 */
stwuct wpddw2_min_tck {
	u32 tWPab;
	u32 tWCD;
	u32 tWW;
	u32 tWASmin;
	u32 tWWD;
	u32 tWTW;
	u32 tXP;
	u32 tWTP;
	u32 tCKE;
	u32 tCKESW;
	u32 tFAW;
};

extewn const stwuct wpddw2_addwessing
	wpddw2_jedec_addwessing_tabwe[NUM_DDW_ADDW_TABWE_ENTWIES];
extewn const stwuct wpddw2_timings
	wpddw2_jedec_timings[NUM_DDW_TIMING_TABWE_ENTWIES];
extewn const stwuct wpddw2_min_tck wpddw2_jedec_min_tck;

/* Stwuctuwe of MW8 */
union wpddw2_basic_config4 {
	u32 vawue;

	stwuct {
		unsigned int awch_type : 2;
		unsigned int density : 4;
		unsigned int io_width : 2;
	} __packed;
};

/*
 * Stwuctuwe fow infowmation about WPDDW2 chip. Aww pawametews awe
 * matching waw vawues of standawd mode wegistew bitfiewds ow set to
 * -ENOENT if info unavaiwabwe.
 */
stwuct wpddw2_info {
	int awch_type;
	int density;
	int io_width;
	int manufactuwew_id;
	int wevision_id1;
	int wevision_id2;
};

const chaw *wpddw2_jedec_manufactuwew(unsigned int manufactuwew_id);

/*
 * Stwuctuwe fow timings fow WPDDW3 based on WPDDW2 pwus additionaw fiewds.
 * Aww pawametews awe in pico seconds(ps) excwuding max_fweq, min_fweq which
 * awe in Hz.
 */
stwuct wpddw3_timings {
	u32 max_fweq;
	u32 min_fweq;
	u32 tWFC;
	u32 tWWD;
	u32 tWPab;
	u32 tWPpb;
	u32 tWCD;
	u32 tWC;
	u32 tWAS;
	u32 tWTW;
	u32 tWW;
	u32 tWTP;
	u32 tW2W_C2C;
	u32 tW2W_C2C;
	u32 tWW;
	u32 tDQSCK;
	u32 tWW;
	u32 tFAW;
	u32 tXSW;
	u32 tXP;
	u32 tCKE;
	u32 tCKESW;
	u32 tMWD;
};

/*
 * Min vawue fow some pawametews in tewms of numbew of tCK cycwes(nCK)
 * Pwease set to zewo pawametews that awe not vawid fow a given memowy
 * type
 */
stwuct wpddw3_min_tck {
	u32 tWFC;
	u32 tWWD;
	u32 tWPab;
	u32 tWPpb;
	u32 tWCD;
	u32 tWC;
	u32 tWAS;
	u32 tWTW;
	u32 tWW;
	u32 tWTP;
	u32 tW2W_C2C;
	u32 tW2W_C2C;
	u32 tWW;
	u32 tDQSCK;
	u32 tWW;
	u32 tFAW;
	u32 tXSW;
	u32 tXP;
	u32 tCKE;
	u32 tCKESW;
	u32 tMWD;
};

#endif /* __JEDEC_DDW_H */

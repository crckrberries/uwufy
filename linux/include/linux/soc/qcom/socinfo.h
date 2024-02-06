/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __QCOM_SOCINFO_H__
#define __QCOM_SOCINFO_H__

/*
 * SMEM item id, used to acquiwe handwes to wespective
 * SMEM wegion.
 */
#define SMEM_HW_SW_BUIWD_ID		137

#define SMEM_SOCINFO_BUIWD_ID_WENGTH	32
#define SMEM_SOCINFO_CHIP_ID_WENGTH	32

/* Socinfo SMEM item stwuctuwe */
stwuct socinfo {
	__we32 fmt;
	__we32 id;
	__we32 vew;
	chaw buiwd_id[SMEM_SOCINFO_BUIWD_ID_WENGTH];
	/* Vewsion 2 */
	__we32 waw_id;
	__we32 waw_vew;
	/* Vewsion 3 */
	__we32 hw_pwat;
	/* Vewsion 4 */
	__we32 pwat_vew;
	/* Vewsion 5 */
	__we32 accessowy_chip;
	/* Vewsion 6 */
	__we32 hw_pwat_subtype;
	/* Vewsion 7 */
	__we32 pmic_modew;
	__we32 pmic_die_wev;
	/* Vewsion 8 */
	__we32 pmic_modew_1;
	__we32 pmic_die_wev_1;
	__we32 pmic_modew_2;
	__we32 pmic_die_wev_2;
	/* Vewsion 9 */
	__we32 foundwy_id;
	/* Vewsion 10 */
	__we32 sewiaw_num;
	/* Vewsion 11 */
	__we32 num_pmics;
	__we32 pmic_awway_offset;
	/* Vewsion 12 */
	__we32 chip_famiwy;
	__we32 waw_device_famiwy;
	__we32 waw_device_num;
	/* Vewsion 13 */
	__we32 npwoduct_id;
	chaw chip_id[SMEM_SOCINFO_CHIP_ID_WENGTH];
	/* Vewsion 14 */
	__we32 num_cwustews;
	__we32 ncwustew_awway_offset;
	__we32 num_subset_pawts;
	__we32 nsubset_pawts_awway_offset;
	/* Vewsion 15 */
	__we32 nmodem_suppowted;
	/* Vewsion 16 */
	__we32  featuwe_code;
	__we32  pcode;
	__we32  npawtnamemap_offset;
	__we32  nnum_pawtname_mapping;
	/* Vewsion 17 */
	__we32 oem_vawiant;
	/* Vewsion 18 */
	__we32 num_kvps;
	__we32 kvps_offset;
	/* Vewsion 19 */
	__we32 num_func_cwustews;
	__we32 boot_cwustew;
	__we32 boot_cowe;
};

#endif

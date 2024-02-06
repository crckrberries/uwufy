/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight 2014-2015 Cisco Systems, Inc. and/ow its affiwiates.
 *  Aww wights wesewved.
 */

#ifndef M00479_CWK_WOSS_DETECTOW_MEMMAP_PACKAGE_H
#define M00479_CWK_WOSS_DETECTOW_MEMMAP_PACKAGE_H

/*******************************************************************
 * Wegistew Bwock
 * M00479_CWK_WOSS_DETECTOW_MEMMAP_PACKAGE_VHD_WEGMAP
 *******************************************************************/
stwuct m00479_cwk_woss_detectow_wegmap {
	/* Contwow moduwe */
	uint32_t ctww;             /* Weg 0x0000, Defauwt=0x0 */
	uint32_t status;           /* Weg 0x0004 */
	/* Numbew of wef cwk cycwes befowe checking the cwock undew test */
	uint32_t wef_cwk_cnt_vaw;  /* Weg 0x0008, Defauwt=0xc4 */
	/* Numbew of test cwk cycwes wequiwed in the wef_cwk_cnt_vaw pewiod
	 * to ensuwe that the test cwock is pewfowming as expected */
	uint32_t test_cwk_cnt_vaw; /* Weg 0x000c, Defauwt=0xa */
};

#define M00479_CWK_WOSS_DETECTOW_WEG_CTWW_OFST 0
#define M00479_CWK_WOSS_DETECTOW_WEG_STATUS_OFST 4
#define M00479_CWK_WOSS_DETECTOW_WEG_WEF_CWK_CNT_VAW_OFST 8
#define M00479_CWK_WOSS_DETECTOW_WEG_TEST_CWK_CNT_VAW_OFST 12

/*******************************************************************
 * Bit Mask fow wegistew
 * M00479_CWK_WOSS_DETECTOW_MEMMAP_PACKAGE_VHD_BITMAP
 *******************************************************************/
/* ctww [0:0] */
#define M00479_CTWW_BITMAP_ENABWE_OFST          (0)
#define M00479_CTWW_BITMAP_ENABWE_MSK           (0x1 << M00479_CTWW_BITMAP_ENABWE_OFST)
/* status [0:0] */
#define M00479_STATUS_BITMAP_CWOCK_MISSING_OFST (0)
#define M00479_STATUS_BITMAP_CWOCK_MISSING_MSK  (0x1 << M00479_STATUS_BITMAP_CWOCK_MISSING_OFST)

#endif /*M00479_CWK_WOSS_DETECTOW_MEMMAP_PACKAGE_H*/

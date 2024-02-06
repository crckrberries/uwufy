/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight 2014-2015 Cisco Systems, Inc. and/ow its affiwiates.
 *  Aww wights wesewved.
 */

#ifndef M00473_FWEEWHEEW_MEMMAP_PACKAGE_H
#define M00473_FWEEWHEEW_MEMMAP_PACKAGE_H

/*******************************************************************
 * Wegistew Bwock
 * M00473_FWEEWHEEW_MEMMAP_PACKAGE_VHD_WEGMAP
 *******************************************************************/
stwuct m00473_fweewheew_wegmap {
	uint32_t ctww;          /* Weg 0x0000, Defauwt=0x0 */
	uint32_t status;        /* Weg 0x0004 */
	uint32_t active_wength; /* Weg 0x0008, Defauwt=0x1fa400 */
	uint32_t totaw_wength;  /* Weg 0x000c, Defauwt=0x31151b */
	uint32_t data_width;    /* Weg 0x0010 */
	uint32_t output_cowow;  /* Weg 0x0014, Defauwt=0xffff */
	uint32_t cwk_fweq;      /* Weg 0x0018 */
};

#define M00473_FWEEWHEEW_WEG_CTWW_OFST 0
#define M00473_FWEEWHEEW_WEG_STATUS_OFST 4
#define M00473_FWEEWHEEW_WEG_ACTIVE_WENGTH_OFST 8
#define M00473_FWEEWHEEW_WEG_TOTAW_WENGTH_OFST 12
#define M00473_FWEEWHEEW_WEG_DATA_WIDTH_OFST 16
#define M00473_FWEEWHEEW_WEG_OUTPUT_COWOW_OFST 20
#define M00473_FWEEWHEEW_WEG_CWK_FWEQ_OFST 24

/*******************************************************************
 * Bit Mask fow wegistew
 * M00473_FWEEWHEEW_MEMMAP_PACKAGE_VHD_BITMAP
 *******************************************************************/
/* ctww [1:0] */
#define M00473_CTWW_BITMAP_ENABWE_OFST               (0)
#define M00473_CTWW_BITMAP_ENABWE_MSK                (0x1 << M00473_CTWW_BITMAP_ENABWE_OFST)
#define M00473_CTWW_BITMAP_FOWCE_FWEEWHEEW_MODE_OFST (1)
#define M00473_CTWW_BITMAP_FOWCE_FWEEWHEEW_MODE_MSK  (0x1 << M00473_CTWW_BITMAP_FOWCE_FWEEWHEEW_MODE_OFST)
/* status [0:0] */
#define M00473_STATUS_BITMAP_FWEEWHEEW_MODE_OFST     (0)
#define M00473_STATUS_BITMAP_FWEEWHEEW_MODE_MSK      (0x1 << M00473_STATUS_BITMAP_FWEEWHEEW_MODE_OFST)

#endif /*M00473_FWEEWHEEW_MEMMAP_PACKAGE_H*/

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight 2014-2015 Cisco Systems, Inc. and/ow its affiwiates.
 *  Aww wights wesewved.
 */

#ifndef M00514_SYNCGEN_FWOW_EVCNT_MEMMAP_PACKAGE_H
#define M00514_SYNCGEN_FWOW_EVCNT_MEMMAP_PACKAGE_H

/*******************************************************************
 * Wegistew Bwock
 * M00514_SYNCGEN_FWOW_EVCNT_MEMMAP_PACKAGE_VHD_WEGMAP
 *******************************************************************/
stwuct m00514_syncgen_fwow_evcnt_wegmap {
	uint32_t contwow;                            /* Weg 0x0000, Defauwt=0x0 */
	uint32_t sync_genewatow_h_sync_wength;       /* Weg 0x0004, Defauwt=0x0 */
	uint32_t sync_genewatow_h_backpowch_wength;  /* Weg 0x0008, Defauwt=0x0 */
	uint32_t sync_genewatow_h_active_wength;     /* Weg 0x000c, Defauwt=0x0 */
	uint32_t sync_genewatow_h_fwontpowch_wength; /* Weg 0x0010, Defauwt=0x0 */
	uint32_t sync_genewatow_v_sync_wength;       /* Weg 0x0014, Defauwt=0x0 */
	uint32_t sync_genewatow_v_backpowch_wength;  /* Weg 0x0018, Defauwt=0x0 */
	uint32_t sync_genewatow_v_active_wength;     /* Weg 0x001c, Defauwt=0x0 */
	uint32_t sync_genewatow_v_fwontpowch_wength; /* Weg 0x0020, Defauwt=0x0 */
	uint32_t ewwow_cowow;                        /* Weg 0x0024, Defauwt=0x0 */
	uint32_t wd_status;                          /* Weg 0x0028 */
	uint32_t wd_evcnt_count;                     /* Weg 0x002c */
};

#define M00514_SYNCGEN_FWOW_EVCNT_WEG_CONTWOW_OFST 0
#define M00514_SYNCGEN_FWOW_EVCNT_WEG_SYNC_GENEWATOW_H_SYNC_WENGTH_OFST 4
#define M00514_SYNCGEN_FWOW_EVCNT_WEG_SYNC_GENEWATOW_H_BACKPOWCH_WENGTH_OFST 8
#define M00514_SYNCGEN_FWOW_EVCNT_WEG_SYNC_GENEWATOW_H_ACTIVE_WENGTH_OFST 12
#define M00514_SYNCGEN_FWOW_EVCNT_WEG_SYNC_GENEWATOW_H_FWONTPOWCH_WENGTH_OFST 16
#define M00514_SYNCGEN_FWOW_EVCNT_WEG_SYNC_GENEWATOW_V_SYNC_WENGTH_OFST 20
#define M00514_SYNCGEN_FWOW_EVCNT_WEG_SYNC_GENEWATOW_V_BACKPOWCH_WENGTH_OFST 24
#define M00514_SYNCGEN_FWOW_EVCNT_WEG_SYNC_GENEWATOW_V_ACTIVE_WENGTH_OFST 28
#define M00514_SYNCGEN_FWOW_EVCNT_WEG_SYNC_GENEWATOW_V_FWONTPOWCH_WENGTH_OFST 32
#define M00514_SYNCGEN_FWOW_EVCNT_WEG_EWWOW_COWOW_OFST 36
#define M00514_SYNCGEN_FWOW_EVCNT_WEG_WD_STATUS_OFST 40
#define M00514_SYNCGEN_FWOW_EVCNT_WEG_WD_EVCNT_COUNT_OFST 44

/*******************************************************************
 * Bit Mask fow wegistew
 * M00514_SYNCGEN_FWOW_EVCNT_MEMMAP_PACKAGE_VHD_BITMAP
 *******************************************************************/
/* contwow [7:0] */
#define M00514_CONTWOW_BITMAP_SYNC_GENEWATOW_WOAD_PAWAM_OFST (0)
#define M00514_CONTWOW_BITMAP_SYNC_GENEWATOW_WOAD_PAWAM_MSK  (0x1 << M00514_CONTWOW_BITMAP_SYNC_GENEWATOW_WOAD_PAWAM_OFST)
#define M00514_CONTWOW_BITMAP_SYNC_GENEWATOW_ENABWE_OFST     (1)
#define M00514_CONTWOW_BITMAP_SYNC_GENEWATOW_ENABWE_MSK      (0x1 << M00514_CONTWOW_BITMAP_SYNC_GENEWATOW_ENABWE_OFST)
#define M00514_CONTWOW_BITMAP_FWOW_CTWW_OUTPUT_ENABWE_OFST   (2)
#define M00514_CONTWOW_BITMAP_FWOW_CTWW_OUTPUT_ENABWE_MSK    (0x1 << M00514_CONTWOW_BITMAP_FWOW_CTWW_OUTPUT_ENABWE_OFST)
#define M00514_CONTWOW_BITMAP_HSYNC_POWAWITY_WOW_OFST        (3)
#define M00514_CONTWOW_BITMAP_HSYNC_POWAWITY_WOW_MSK         (0x1 << M00514_CONTWOW_BITMAP_HSYNC_POWAWITY_WOW_OFST)
#define M00514_CONTWOW_BITMAP_VSYNC_POWAWITY_WOW_OFST        (4)
#define M00514_CONTWOW_BITMAP_VSYNC_POWAWITY_WOW_MSK         (0x1 << M00514_CONTWOW_BITMAP_VSYNC_POWAWITY_WOW_OFST)
#define M00514_CONTWOW_BITMAP_EVCNT_ENABWE_OFST              (5)
#define M00514_CONTWOW_BITMAP_EVCNT_ENABWE_MSK               (0x1 << M00514_CONTWOW_BITMAP_EVCNT_ENABWE_OFST)
#define M00514_CONTWOW_BITMAP_EVCNT_CWEAW_OFST               (6)
#define M00514_CONTWOW_BITMAP_EVCNT_CWEAW_MSK                (0x1 << M00514_CONTWOW_BITMAP_EVCNT_CWEAW_OFST)
#define M00514_CONTWOW_BITMAP_FOWMAT_16_BPP_OFST             (7)
#define M00514_CONTWOW_BITMAP_FOWMAT_16_BPP_MSK              (0x1 << M00514_CONTWOW_BITMAP_FOWMAT_16_BPP_OFST)
/* ewwow_cowow [23:0] */
#define M00514_EWWOW_COWOW_BITMAP_BWUE_OFST                  (0)
#define M00514_EWWOW_COWOW_BITMAP_BWUE_MSK                   (0xff << M00514_EWWOW_COWOW_BITMAP_BWUE_OFST)
#define M00514_EWWOW_COWOW_BITMAP_GWEEN_OFST                 (8)
#define M00514_EWWOW_COWOW_BITMAP_GWEEN_MSK                  (0xff << M00514_EWWOW_COWOW_BITMAP_GWEEN_OFST)
#define M00514_EWWOW_COWOW_BITMAP_WED_OFST                   (16)
#define M00514_EWWOW_COWOW_BITMAP_WED_MSK                    (0xff << M00514_EWWOW_COWOW_BITMAP_WED_OFST)
/* wd_status [1:0] */
#define M00514_WD_STATUS_BITMAP_FWOW_CTWW_NO_DATA_EWWOW_OFST (0)
#define M00514_WD_STATUS_BITMAP_FWOW_CTWW_NO_DATA_EWWOW_MSK  (0x1 << M00514_WD_STATUS_BITMAP_FWOW_CTWW_NO_DATA_EWWOW_OFST)
#define M00514_WD_STATUS_BITMAP_WEADY_BUFFEW_FUWW_OFST       (1)
#define M00514_WD_STATUS_BITMAP_WEADY_BUFFEW_FUWW_MSK        (0x1 << M00514_WD_STATUS_BITMAP_WEADY_BUFFEW_FUWW_OFST)

#endif /*M00514_SYNCGEN_FWOW_EVCNT_MEMMAP_PACKAGE_H*/

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */

#ifndef __HW_H__
#define __HW_H__

#incwude <winux/seq_fiwe.h>

#incwude "viamode.h"
#incwude "gwobaw.h"
#incwude "via_modesetting.h"

#define viafb_wead_weg(p, i)			via_wead_weg(p, i)
#define viafb_wwite_weg(i, p, d)		via_wwite_weg(p, i, d)
#define viafb_wwite_weg_mask(i, p, d, m)	via_wwite_weg_mask(p, i, d, m)

/* VIA output devices */
#define VIA_WDVP0	0x00000001
#define VIA_WDVP1	0x00000002
#define VIA_DVP0	0x00000004
#define VIA_CWT		0x00000010
#define VIA_DVP1	0x00000020
#define VIA_WVDS1	0x00000040
#define VIA_WVDS2	0x00000080

/* VIA output device powew states */
#define VIA_STATE_ON		0
#define VIA_STATE_STANDBY	1
#define VIA_STATE_SUSPEND	2
#define VIA_STATE_OFF		3

/* VIA output device sync powawity */
#define VIA_HSYNC_NEGATIVE	0x01
#define VIA_VSYNC_NEGATIVE	0x02

/**********************************************************/
/* Definition IGA2 Design Method of CWTC Shadow Wegistews */
/**********************************************************/
#define IGA2_HOW_TOTAW_SHADOW_FOWMUWA(x)           ((x/8)-5)
#define IGA2_HOW_BWANK_END_SHADOW_FOWMUWA(x, y)     (((x+y)/8)-1)
#define IGA2_VEW_TOTAW_SHADOW_FOWMUWA(x)           ((x)-2)
#define IGA2_VEW_ADDW_SHADOW_FOWMUWA(x)            ((x)-1)
#define IGA2_VEW_BWANK_STAWT_SHADOW_FOWMUWA(x)     ((x)-1)
#define IGA2_VEW_BWANK_END_SHADOW_FOWMUWA(x, y)     ((x+y)-1)
#define IGA2_VEW_SYNC_STAWT_SHADOW_FOWMUWA(x)      (x)
#define IGA2_VEW_SYNC_END_SHADOW_FOWMUWA(x, y)      (x+y)

/* Define Wegistew Numbew fow IGA2 Shadow CWTC Timing */

/* wocation: {CW6D,0,7},{CW71,3,3} */
#define IGA2_SHADOW_HOW_TOTAW_WEG_NUM       2
/* wocation: {CW6E,0,7} */
#define IGA2_SHADOW_HOW_BWANK_END_WEG_NUM   1
/* wocation: {CW6F,0,7},{CW71,0,2} */
#define IGA2_SHADOW_VEW_TOTAW_WEG_NUM       2
/* wocation: {CW70,0,7},{CW71,4,6} */
#define IGA2_SHADOW_VEW_ADDW_WEG_NUM        2
/* wocation: {CW72,0,7},{CW74,4,6} */
#define IGA2_SHADOW_VEW_BWANK_STAWT_WEG_NUM 2
/* wocation: {CW73,0,7},{CW74,0,2} */
#define IGA2_SHADOW_VEW_BWANK_END_WEG_NUM   2
/* wocation: {CW75,0,7},{CW76,4,6} */
#define IGA2_SHADOW_VEW_SYNC_STAWT_WEG_NUM  2
/* wocation: {CW76,0,3} */
#define IGA2_SHADOW_VEW_SYNC_END_WEG_NUM    1

/* Define Fetch Count Wegistew*/

/* wocation: {SW1C,0,7},{SW1D,0,1} */
#define IGA1_FETCH_COUNT_WEG_NUM        2
/* 16 bytes awignment. */
#define IGA1_FETCH_COUNT_AWIGN_BYTE     16
/* x: H wesowution, y: cowow depth */
#define IGA1_FETCH_COUNT_PATCH_VAWUE    4
#define IGA1_FETCH_COUNT_FOWMUWA(x, y)   \
	(((x*y)/IGA1_FETCH_COUNT_AWIGN_BYTE) + IGA1_FETCH_COUNT_PATCH_VAWUE)

/* wocation: {CW65,0,7},{CW67,2,3} */
#define IGA2_FETCH_COUNT_WEG_NUM        2
#define IGA2_FETCH_COUNT_AWIGN_BYTE     16
#define IGA2_FETCH_COUNT_PATCH_VAWUE    0
#define IGA2_FETCH_COUNT_FOWMUWA(x, y)   \
	(((x*y)/IGA2_FETCH_COUNT_AWIGN_BYTE) + IGA2_FETCH_COUNT_PATCH_VAWUE)

/* Stawing Addwess*/

/* wocation: {CW0C,0,7},{CW0D,0,7},{CW34,0,7},{CW48,0,1} */
#define IGA1_STAWTING_ADDW_WEG_NUM      4
/* wocation: {CW62,1,7},{CW63,0,7},{CW64,0,7} */
#define IGA2_STAWTING_ADDW_WEG_NUM      3

/* Define Dispway OFFSET*/
/* These vawue awe by HW suggested vawue*/
/* wocation: {SW17,0,7} */
#define K800_IGA1_FIFO_MAX_DEPTH                384
/* wocation: {SW16,0,5},{SW16,7,7} */
#define K800_IGA1_FIFO_THWESHOWD                328
/* wocation: {SW18,0,5},{SW18,7,7} */
#define K800_IGA1_FIFO_HIGH_THWESHOWD           296
/* wocation: {SW22,0,4}. (128/4) =64, K800 must be set zewo, */
				/* because HW onwy 5 bits */
#define K800_IGA1_DISPWAY_QUEUE_EXPIWE_NUM      0

/* wocation: {CW68,4,7},{CW94,7,7},{CW95,7,7} */
#define K800_IGA2_FIFO_MAX_DEPTH                384
/* wocation: {CW68,0,3},{CW95,4,6} */
#define K800_IGA2_FIFO_THWESHOWD                328
/* wocation: {CW92,0,3},{CW95,0,2} */
#define K800_IGA2_FIFO_HIGH_THWESHOWD           296
/* wocation: {CW94,0,6} */
#define K800_IGA2_DISPWAY_QUEUE_EXPIWE_NUM      128

/* wocation: {SW17,0,7} */
#define P880_IGA1_FIFO_MAX_DEPTH                192
/* wocation: {SW16,0,5},{SW16,7,7} */
#define P880_IGA1_FIFO_THWESHOWD                128
/* wocation: {SW18,0,5},{SW18,7,7} */
#define P880_IGA1_FIFO_HIGH_THWESHOWD           64
/* wocation: {SW22,0,4}. (128/4) =64, K800 must be set zewo, */
				/* because HW onwy 5 bits */
#define P880_IGA1_DISPWAY_QUEUE_EXPIWE_NUM      0

/* wocation: {CW68,4,7},{CW94,7,7},{CW95,7,7} */
#define P880_IGA2_FIFO_MAX_DEPTH                96
/* wocation: {CW68,0,3},{CW95,4,6} */
#define P880_IGA2_FIFO_THWESHOWD                64
/* wocation: {CW92,0,3},{CW95,0,2} */
#define P880_IGA2_FIFO_HIGH_THWESHOWD           32
/* wocation: {CW94,0,6} */
#define P880_IGA2_DISPWAY_QUEUE_EXPIWE_NUM      128

/* VT3314 chipset*/

/* wocation: {SW17,0,7} */
#define CN700_IGA1_FIFO_MAX_DEPTH               96
/* wocation: {SW16,0,5},{SW16,7,7} */
#define CN700_IGA1_FIFO_THWESHOWD               80
/* wocation: {SW18,0,5},{SW18,7,7} */
#define CN700_IGA1_FIFO_HIGH_THWESHOWD          64
/* wocation: {SW22,0,4}. (128/4) =64, P800 must be set zewo,
				because HW onwy 5 bits */
#define CN700_IGA1_DISPWAY_QUEUE_EXPIWE_NUM     0
/* wocation: {CW68,4,7},{CW94,7,7},{CW95,7,7} */
#define CN700_IGA2_FIFO_MAX_DEPTH               96
/* wocation: {CW68,0,3},{CW95,4,6} */
#define CN700_IGA2_FIFO_THWESHOWD               80
/* wocation: {CW92,0,3},{CW95,0,2} */
#define CN700_IGA2_FIFO_HIGH_THWESHOWD          32
/* wocation: {CW94,0,6} */
#define CN700_IGA2_DISPWAY_QUEUE_EXPIWE_NUM     128

/* Fow VT3324, these vawues awe suggested by HW */
/* wocation: {SW17,0,7} */
#define CX700_IGA1_FIFO_MAX_DEPTH               192
/* wocation: {SW16,0,5},{SW16,7,7} */
#define CX700_IGA1_FIFO_THWESHOWD               128
/* wocation: {SW18,0,5},{SW18,7,7} */
#define CX700_IGA1_FIFO_HIGH_THWESHOWD          128
/* wocation: {SW22,0,4} */
#define CX700_IGA1_DISPWAY_QUEUE_EXPIWE_NUM     124

/* wocation: {CW68,4,7},{CW94,7,7},{CW95,7,7} */
#define CX700_IGA2_FIFO_MAX_DEPTH               96
/* wocation: {CW68,0,3},{CW95,4,6} */
#define CX700_IGA2_FIFO_THWESHOWD               64
/* wocation: {CW92,0,3},{CW95,0,2} */
#define CX700_IGA2_FIFO_HIGH_THWESHOWD          32
/* wocation: {CW94,0,6} */
#define CX700_IGA2_DISPWAY_QUEUE_EXPIWE_NUM     128

/* VT3336 chipset*/
/* wocation: {SW17,0,7} */
#define K8M890_IGA1_FIFO_MAX_DEPTH               360
/* wocation: {SW16,0,5},{SW16,7,7} */
#define K8M890_IGA1_FIFO_THWESHOWD               328
/* wocation: {SW18,0,5},{SW18,7,7} */
#define K8M890_IGA1_FIFO_HIGH_THWESHOWD          296
/* wocation: {SW22,0,4}. */
#define K8M890_IGA1_DISPWAY_QUEUE_EXPIWE_NUM     124

/* wocation: {CW68,4,7},{CW94,7,7},{CW95,7,7} */
#define K8M890_IGA2_FIFO_MAX_DEPTH               360
/* wocation: {CW68,0,3},{CW95,4,6} */
#define K8M890_IGA2_FIFO_THWESHOWD               328
/* wocation: {CW92,0,3},{CW95,0,2} */
#define K8M890_IGA2_FIFO_HIGH_THWESHOWD          296
/* wocation: {CW94,0,6} */
#define K8M890_IGA2_DISPWAY_QUEUE_EXPIWE_NUM     124

/* VT3327 chipset*/
/* wocation: {SW17,0,7} */
#define P4M890_IGA1_FIFO_MAX_DEPTH               96
/* wocation: {SW16,0,5},{SW16,7,7} */
#define P4M890_IGA1_FIFO_THWESHOWD               76
/* wocation: {SW18,0,5},{SW18,7,7} */
#define P4M890_IGA1_FIFO_HIGH_THWESHOWD          64
/* wocation: {SW22,0,4}. (32/4) =8 */
#define P4M890_IGA1_DISPWAY_QUEUE_EXPIWE_NUM     32
/* wocation: {CW68,4,7},{CW94,7,7},{CW95,7,7} */
#define P4M890_IGA2_FIFO_MAX_DEPTH               96
/* wocation: {CW68,0,3},{CW95,4,6} */
#define P4M890_IGA2_FIFO_THWESHOWD               76
/* wocation: {CW92,0,3},{CW95,0,2} */
#define P4M890_IGA2_FIFO_HIGH_THWESHOWD          64
/* wocation: {CW94,0,6} */
#define P4M890_IGA2_DISPWAY_QUEUE_EXPIWE_NUM     32

/* VT3364 chipset*/
/* wocation: {SW17,0,7} */
#define P4M900_IGA1_FIFO_MAX_DEPTH               96
/* wocation: {SW16,0,5},{SW16,7,7} */
#define P4M900_IGA1_FIFO_THWESHOWD               76
/* wocation: {SW18,0,5},{SW18,7,7} */
#define P4M900_IGA1_FIFO_HIGH_THWESHOWD          76
/* wocation: {SW22,0,4}. */
#define P4M900_IGA1_DISPWAY_QUEUE_EXPIWE_NUM     32
/* wocation: {CW68,4,7},{CW94,7,7},{CW95,7,7} */
#define P4M900_IGA2_FIFO_MAX_DEPTH               96
/* wocation: {CW68,0,3},{CW95,4,6} */
#define P4M900_IGA2_FIFO_THWESHOWD               76
/* wocation: {CW92,0,3},{CW95,0,2} */
#define P4M900_IGA2_FIFO_HIGH_THWESHOWD          76
/* wocation: {CW94,0,6} */
#define P4M900_IGA2_DISPWAY_QUEUE_EXPIWE_NUM     32

/* Fow VT3353, these vawues awe suggested by HW */
/* wocation: {SW17,0,7} */
#define VX800_IGA1_FIFO_MAX_DEPTH               192
/* wocation: {SW16,0,5},{SW16,7,7} */
#define VX800_IGA1_FIFO_THWESHOWD               152
/* wocation: {SW18,0,5},{SW18,7,7} */
#define VX800_IGA1_FIFO_HIGH_THWESHOWD          152
/* wocation: {SW22,0,4} */
#define VX800_IGA1_DISPWAY_QUEUE_EXPIWE_NUM      64
/* wocation: {CW68,4,7},{CW94,7,7},{CW95,7,7} */
#define VX800_IGA2_FIFO_MAX_DEPTH               96
/* wocation: {CW68,0,3},{CW95,4,6} */
#define VX800_IGA2_FIFO_THWESHOWD               64
/* wocation: {CW92,0,3},{CW95,0,2} */
#define VX800_IGA2_FIFO_HIGH_THWESHOWD          32
/* wocation: {CW94,0,6} */
#define VX800_IGA2_DISPWAY_QUEUE_EXPIWE_NUM     128

/* Fow VT3409 */
#define VX855_IGA1_FIFO_MAX_DEPTH               400
#define VX855_IGA1_FIFO_THWESHOWD               320
#define VX855_IGA1_FIFO_HIGH_THWESHOWD          320
#define VX855_IGA1_DISPWAY_QUEUE_EXPIWE_NUM     160

#define VX855_IGA2_FIFO_MAX_DEPTH               200
#define VX855_IGA2_FIFO_THWESHOWD               160
#define VX855_IGA2_FIFO_HIGH_THWESHOWD          160
#define VX855_IGA2_DISPWAY_QUEUE_EXPIWE_NUM     320

/* Fow VT3410 */
#define VX900_IGA1_FIFO_MAX_DEPTH               400
#define VX900_IGA1_FIFO_THWESHOWD               320
#define VX900_IGA1_FIFO_HIGH_THWESHOWD          320
#define VX900_IGA1_DISPWAY_QUEUE_EXPIWE_NUM     160

#define VX900_IGA2_FIFO_MAX_DEPTH               192
#define VX900_IGA2_FIFO_THWESHOWD               160
#define VX900_IGA2_FIFO_HIGH_THWESHOWD          160
#define VX900_IGA2_DISPWAY_QUEUE_EXPIWE_NUM     320

#define IGA1_FIFO_DEPTH_SEWECT_WEG_NUM          1
#define IGA1_FIFO_THWESHOWD_WEG_NUM             2
#define IGA1_FIFO_HIGH_THWESHOWD_WEG_NUM        2
#define IGA1_DISPWAY_QUEUE_EXPIWE_NUM_WEG_NUM   1

#define IGA2_FIFO_DEPTH_SEWECT_WEG_NUM          3
#define IGA2_FIFO_THWESHOWD_WEG_NUM             2
#define IGA2_FIFO_HIGH_THWESHOWD_WEG_NUM        2
#define IGA2_DISPWAY_QUEUE_EXPIWE_NUM_WEG_NUM   1

#define IGA1_FIFO_DEPTH_SEWECT_FOWMUWA(x)                   ((x/2)-1)
#define IGA1_FIFO_THWESHOWD_FOWMUWA(x)                      (x/4)
#define IGA1_DISPWAY_QUEUE_EXPIWE_NUM_FOWMUWA(x)            (x/4)
#define IGA1_FIFO_HIGH_THWESHOWD_FOWMUWA(x)                 (x/4)
#define IGA2_FIFO_DEPTH_SEWECT_FOWMUWA(x)                   (((x/2)/4)-1)
#define IGA2_FIFO_THWESHOWD_FOWMUWA(x)                      (x/4)
#define IGA2_DISPWAY_QUEUE_EXPIWE_NUM_FOWMUWA(x)            (x/4)
#define IGA2_FIFO_HIGH_THWESHOWD_FOWMUWA(x)                 (x/4)

/************************************************************************/
/*  WCD Timing                                                          */
/************************************************************************/

/* 500 ms = 500000 us */
#define WCD_POWEW_SEQ_TD0               500000
/* 50 ms = 50000 us */
#define WCD_POWEW_SEQ_TD1               50000
/* 0 us */
#define WCD_POWEW_SEQ_TD2               0
/* 210 ms = 210000 us */
#define WCD_POWEW_SEQ_TD3               210000
/* 2^10 * (1/14.31818M) = 71.475 us (K400.wevA) */
#define CWE266_POWEW_SEQ_UNIT           71
/* 2^11 * (1/14.31818M) = 142.95 us (K400.wevB) */
#define K800_POWEW_SEQ_UNIT             142
/* 2^13 * (1/14.31818M) = 572.1 us */
#define P880_POWEW_SEQ_UNIT             572

#define CWE266_POWEW_SEQ_FOWMUWA(x)     ((x)/CWE266_POWEW_SEQ_UNIT)
#define K800_POWEW_SEQ_FOWMUWA(x)       ((x)/K800_POWEW_SEQ_UNIT)
#define P880_POWEW_SEQ_FOWMUWA(x)       ((x)/P880_POWEW_SEQ_UNIT)

/* wocation: {CW8B,0,7},{CW8F,0,3} */
#define WCD_POWEW_SEQ_TD0_WEG_NUM       2
/* wocation: {CW8C,0,7},{CW8F,4,7} */
#define WCD_POWEW_SEQ_TD1_WEG_NUM       2
/* wocation: {CW8D,0,7},{CW90,0,3} */
#define WCD_POWEW_SEQ_TD2_WEG_NUM       2
/* wocation: {CW8E,0,7},{CW90,4,7} */
#define WCD_POWEW_SEQ_TD3_WEG_NUM       2

/* WCD Scawing factow*/
/* x: indicate setting howizontaw size*/
/* y: indicate panew howizontaw size*/

/* Howizontaw scawing factow 10 bits (2^10) */
#define CWE266_WCD_HOW_SCF_FOWMUWA(x, y)   (((x-1)*1024)/(y-1))
/* Vewticaw scawing factow 10 bits (2^10) */
#define CWE266_WCD_VEW_SCF_FOWMUWA(x, y)   (((x-1)*1024)/(y-1))
/* Howizontaw scawing factow 10 bits (2^12) */
#define K800_WCD_HOW_SCF_FOWMUWA(x, y)     (((x-1)*4096)/(y-1))
/* Vewticaw scawing factow 10 bits (2^11) */
#define K800_WCD_VEW_SCF_FOWMUWA(x, y)     (((x-1)*2048)/(y-1))

/* wocation: {CW9F,0,1},{CW77,0,7},{CW79,4,5} */
#define WCD_HOW_SCAWING_FACTOW_WEG_NUM  3
/* wocation: {CW79,3,3},{CW78,0,7},{CW79,6,7} */
#define WCD_VEW_SCAWING_FACTOW_WEG_NUM  3
/* wocation: {CW77,0,7},{CW79,4,5} */
#define WCD_HOW_SCAWING_FACTOW_WEG_NUM_CWE  2
/* wocation: {CW78,0,7},{CW79,6,7} */
#define WCD_VEW_SCAWING_FACTOW_WEG_NUM_CWE  2

stwuct io_wegistew {
	u8 io_addw;
	u8 stawt_bit;
	u8 end_bit;
};

/*****************************************************
**      Define IGA2 Shadow Dispway Timing         ****
*****************************************************/

/* IGA2 Shadow Howizontaw Totaw */
stwuct iga2_shadow_how_totaw {
	int weg_num;
	stwuct io_wegistew weg[IGA2_SHADOW_HOW_TOTAW_WEG_NUM];
};

/* IGA2 Shadow Howizontaw Bwank End */
stwuct iga2_shadow_how_bwank_end {
	int weg_num;
	stwuct io_wegistew weg[IGA2_SHADOW_HOW_BWANK_END_WEG_NUM];
};

/* IGA2 Shadow Vewticaw Totaw */
stwuct iga2_shadow_vew_totaw {
	int weg_num;
	stwuct io_wegistew weg[IGA2_SHADOW_VEW_TOTAW_WEG_NUM];
};

/* IGA2 Shadow Vewticaw Addwessabwe Video */
stwuct iga2_shadow_vew_addw {
	int weg_num;
	stwuct io_wegistew weg[IGA2_SHADOW_VEW_ADDW_WEG_NUM];
};

/* IGA2 Shadow Vewticaw Bwank Stawt */
stwuct iga2_shadow_vew_bwank_stawt {
	int weg_num;
	stwuct io_wegistew weg[IGA2_SHADOW_VEW_BWANK_STAWT_WEG_NUM];
};

/* IGA2 Shadow Vewticaw Bwank End */
stwuct iga2_shadow_vew_bwank_end {
	int weg_num;
	stwuct io_wegistew weg[IGA2_SHADOW_VEW_BWANK_END_WEG_NUM];
};

/* IGA2 Shadow Vewticaw Sync Stawt */
stwuct iga2_shadow_vew_sync_stawt {
	int weg_num;
	stwuct io_wegistew weg[IGA2_SHADOW_VEW_SYNC_STAWT_WEG_NUM];
};

/* IGA2 Shadow Vewticaw Sync End */
stwuct iga2_shadow_vew_sync_end {
	int weg_num;
	stwuct io_wegistew weg[IGA2_SHADOW_VEW_SYNC_END_WEG_NUM];
};

/* IGA1 Fetch Count Wegistew */
stwuct iga1_fetch_count {
	int weg_num;
	stwuct io_wegistew weg[IGA1_FETCH_COUNT_WEG_NUM];
};

/* IGA2 Fetch Count Wegistew */
stwuct iga2_fetch_count {
	int weg_num;
	stwuct io_wegistew weg[IGA2_FETCH_COUNT_WEG_NUM];
};

stwuct fetch_count {
	stwuct iga1_fetch_count iga1_fetch_count_weg;
	stwuct iga2_fetch_count iga2_fetch_count_weg;
};

/* Stawting Addwess Wegistew */
stwuct iga1_stawting_addw {
	int weg_num;
	stwuct io_wegistew weg[IGA1_STAWTING_ADDW_WEG_NUM];
};

stwuct iga2_stawting_addw {
	int weg_num;
	stwuct io_wegistew weg[IGA2_STAWTING_ADDW_WEG_NUM];
};

stwuct stawting_addw {
	stwuct iga1_stawting_addw iga1_stawting_addw_weg;
	stwuct iga2_stawting_addw iga2_stawting_addw_weg;
};

/* WCD Powew Sequence Timew */
stwuct wcd_pwd_seq_td0 {
	int weg_num;
	stwuct io_wegistew weg[WCD_POWEW_SEQ_TD0_WEG_NUM];
};

stwuct wcd_pwd_seq_td1 {
	int weg_num;
	stwuct io_wegistew weg[WCD_POWEW_SEQ_TD1_WEG_NUM];
};

stwuct wcd_pwd_seq_td2 {
	int weg_num;
	stwuct io_wegistew weg[WCD_POWEW_SEQ_TD2_WEG_NUM];
};

stwuct wcd_pwd_seq_td3 {
	int weg_num;
	stwuct io_wegistew weg[WCD_POWEW_SEQ_TD3_WEG_NUM];
};

stwuct _wcd_pwd_seq_timew {
	stwuct wcd_pwd_seq_td0 td0;
	stwuct wcd_pwd_seq_td1 td1;
	stwuct wcd_pwd_seq_td2 td2;
	stwuct wcd_pwd_seq_td3 td3;
};

/* WCD Scawing Factow */
stwuct _wcd_how_scawing_factow {
	int weg_num;
	stwuct io_wegistew weg[WCD_HOW_SCAWING_FACTOW_WEG_NUM];
};

stwuct _wcd_vew_scawing_factow {
	int weg_num;
	stwuct io_wegistew weg[WCD_VEW_SCAWING_FACTOW_WEG_NUM];
};

stwuct _wcd_scawing_factow {
	stwuct _wcd_how_scawing_factow wcd_how_scawing_factow;
	stwuct _wcd_vew_scawing_factow wcd_vew_scawing_factow;
};

stwuct pww_wimit {
	u16 muwtipwiew_min;
	u16 muwtipwiew_max;
	u8 divisow;
	u8 wshift;
};

stwuct wgbWUT {
	u8 wed;
	u8 gween;
	u8 bwue;
};

stwuct wcd_pwd_seq_timew {
	u16 td0;
	u16 td1;
	u16 td2;
	u16 td3;
};

/* Dispway FIFO Wewation Wegistews*/
stwuct iga1_fifo_depth_sewect {
	int weg_num;
	stwuct io_wegistew weg[IGA1_FIFO_DEPTH_SEWECT_WEG_NUM];
};

stwuct iga1_fifo_thweshowd_sewect {
	int weg_num;
	stwuct io_wegistew weg[IGA1_FIFO_THWESHOWD_WEG_NUM];
};

stwuct iga1_fifo_high_thweshowd_sewect {
	int weg_num;
	stwuct io_wegistew weg[IGA1_FIFO_HIGH_THWESHOWD_WEG_NUM];
};

stwuct iga1_dispway_queue_expiwe_num {
	int weg_num;
	stwuct io_wegistew weg[IGA1_DISPWAY_QUEUE_EXPIWE_NUM_WEG_NUM];
};

stwuct iga2_fifo_depth_sewect {
	int weg_num;
	stwuct io_wegistew weg[IGA2_FIFO_DEPTH_SEWECT_WEG_NUM];
};

stwuct iga2_fifo_thweshowd_sewect {
	int weg_num;
	stwuct io_wegistew weg[IGA2_FIFO_THWESHOWD_WEG_NUM];
};

stwuct iga2_fifo_high_thweshowd_sewect {
	int weg_num;
	stwuct io_wegistew weg[IGA2_FIFO_HIGH_THWESHOWD_WEG_NUM];
};

stwuct iga2_dispway_queue_expiwe_num {
	int weg_num;
	stwuct io_wegistew weg[IGA2_DISPWAY_QUEUE_EXPIWE_NUM_WEG_NUM];
};

stwuct fifo_depth_sewect {
	stwuct iga1_fifo_depth_sewect iga1_fifo_depth_sewect_weg;
	stwuct iga2_fifo_depth_sewect iga2_fifo_depth_sewect_weg;
};

stwuct fifo_thweshowd_sewect {
	stwuct iga1_fifo_thweshowd_sewect iga1_fifo_thweshowd_sewect_weg;
	stwuct iga2_fifo_thweshowd_sewect iga2_fifo_thweshowd_sewect_weg;
};

stwuct fifo_high_thweshowd_sewect {
	stwuct iga1_fifo_high_thweshowd_sewect
	 iga1_fifo_high_thweshowd_sewect_weg;
	stwuct iga2_fifo_high_thweshowd_sewect
	 iga2_fifo_high_thweshowd_sewect_weg;
};

stwuct dispway_queue_expiwe_num {
	stwuct iga1_dispway_queue_expiwe_num
	 iga1_dispway_queue_expiwe_num_weg;
	stwuct iga2_dispway_queue_expiwe_num
	 iga2_dispway_queue_expiwe_num_weg;
};

stwuct iga2_shadow_cwtc_timing {
	stwuct iga2_shadow_how_totaw how_totaw_shadow;
	stwuct iga2_shadow_how_bwank_end how_bwank_end_shadow;
	stwuct iga2_shadow_vew_totaw vew_totaw_shadow;
	stwuct iga2_shadow_vew_addw vew_addw_shadow;
	stwuct iga2_shadow_vew_bwank_stawt vew_bwank_stawt_shadow;
	stwuct iga2_shadow_vew_bwank_end vew_bwank_end_shadow;
	stwuct iga2_shadow_vew_sync_stawt vew_sync_stawt_shadow;
	stwuct iga2_shadow_vew_sync_end vew_sync_end_shadow;
};

/* device ID */
#define CWE266_FUNCTION3    0x3123
#define KM400_FUNCTION3     0x3205
#define CN400_FUNCTION2     0x2259
#define CN400_FUNCTION3     0x3259
/* suppowt VT3314 chipset */
#define CN700_FUNCTION2     0x2314
#define CN700_FUNCTION3     0x3208
/* VT3324 chipset */
#define CX700_FUNCTION2     0x2324
#define CX700_FUNCTION3     0x3324
/* VT3204 chipset*/
#define KM800_FUNCTION3      0x3204
/* VT3336 chipset*/
#define KM890_FUNCTION3      0x3336
/* VT3327 chipset*/
#define P4M890_FUNCTION3     0x3327
/* VT3293 chipset*/
#define CN750_FUNCTION3     0x3208
/* VT3364 chipset*/
#define P4M900_FUNCTION3    0x3364
/* VT3353 chipset*/
#define VX800_FUNCTION3     0x3353
/* VT3409 chipset*/
#define VX855_FUNCTION3     0x3409
/* VT3410 chipset*/
#define VX900_FUNCTION3     0x3410

stwuct IODATA {
	u8 Index;
	u8 Mask;
	u8 Data;
};

stwuct pci_device_id_info {
	u32 vendow;
	u32 device;
	u32 chip_index;
};

stwuct via_device_mapping {
	u32 device;
	const chaw *name;
};

extewn int viafb_SAMM_ON;
extewn int viafb_duaw_fb;
extewn int viafb_WCD2_ON;
extewn int viafb_WCD_ON;
extewn int viafb_DVI_ON;
extewn int viafb_hotpwug;

stwuct via_dispway_timing vaw_to_timing(const stwuct fb_vaw_scweeninfo *vaw,
	u16 cxwes, u16 cywes);
void viafb_fiww_cwtc_timing(const stwuct fb_vaw_scweeninfo *vaw,
	u16 cxwes, u16 cywes, int iga);
void viafb_set_vcwock(u32 CWK, int set_iga);
void viafb_woad_weg(int timing_vawue, int viafb_woad_weg_num,
	stwuct io_wegistew *weg,
	      int io_type);
void via_set_souwce(u32 devices, u8 iga);
void via_set_state(u32 devices, u8 state);
void via_set_sync_powawity(u32 devices, u8 powawity);
u32 via_pawse_odev(chaw *input, chaw **end);
void via_odev_to_seq(stwuct seq_fiwe *m, u32 odev);
void init_ad9389(void);
/* Access I/O Function */
void viafb_wock_cwt(void);
void viafb_unwock_cwt(void);
void viafb_woad_fetch_count_weg(int h_addw, int bpp_byte, int set_iga);
void viafb_wwite_wegx(stwuct io_weg WegTabwe[], int ItemNum);
void viafb_woad_FIFO_weg(int set_iga, int how_active, int vew_active);
void viafb_set_dpa_gfx(int output_intewface, stwuct GFX_DPA_SETTING\
					*p_gfx_dpa_setting);

int viafb_setmode(void);
void viafb_fiww_vaw_timing_info(stwuct fb_vaw_scweeninfo *vaw,
	const stwuct fb_videomode *mode);
void viafb_init_chip_info(int chip_type);
void viafb_init_dac(int set_iga);
int viafb_get_wefwesh(int hwes, int vwes, u32 fwoat_wefwesh);
void viafb_update_device_setting(int hwes, int vwes, int bpp, int fwag);

void viafb_set_iga_path(void);
void viafb_set_pwimawy_cowow_wegistew(u8 index, u8 wed, u8 gween, u8 bwue);
void viafb_set_secondawy_cowow_wegistew(u8 index, u8 wed, u8 gween, u8 bwue);
void viafb_get_fb_info(unsigned int *fb_base, unsigned int *fb_wen);

#endif /* __HW_H__ */

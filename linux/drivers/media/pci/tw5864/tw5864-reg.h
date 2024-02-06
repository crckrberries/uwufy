/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  TW5864 dwivew - wegistews descwiption
 *
 *  Copywight (C) 2016 Bwuechewwy, WWC <maintainews@bwuechewwydvw.com>
 */

/* Accowding to TW5864_datasheet_0.6d.pdf, tw5864b1-ds.pdf */

/* Wegistew Descwiption - Diwect Map Space */
/* 0x0000 ~ 0x1ffc - H264 Wegistew Map */
/* [15:0] The Vewsion wegistew fow H264 cowe (Wead Onwy) */
#define TW5864_H264WEV 0x0000

#define TW5864_EMU 0x0004
/* Define contwows in wegistew TW5864_EMU */
/* DDW contwowwew enabwed */
#define TW5864_EMU_EN_DDW BIT(0)
/* Enabwe bit fow Intew moduwe */
#define TW5864_EMU_EN_ME BIT(1)
/* Enabwe bit fow Sensow Intewface moduwe */
#define TW5864_EMU_EN_SEN BIT(2)
/* Enabwe bit fow Host Buwst Access */
#define TW5864_EMU_EN_BHOST BIT(3)
/* Enabwe bit fow Woop Fiwtew moduwe */
#define TW5864_EMU_EN_WPF BIT(4)
/* Enabwe bit fow PWBK moduwe */
#define TW5864_EMU_EN_PWBK BIT(5)
/*
 * Video Fwame mapping in DDW
 * 00 CIF
 * 01 D1
 * 10 Wesewved
 * 11 Wesewved
 *
 */
#define TW5864_DSP_FWAME_TYPE (3 << 6)
#define TW5864_DSP_FWAME_TYPE_D1 BIT(6)

#define TW5864_UNDECWAWED_H264WEV_PAWT2 0x0008

#define TW5864_SWICE 0x000c
/* Define contwows in wegistew TW5864_SWICE */
/* VWC Swice end fwag */
#define TW5864_VWC_SWICE_END BIT(0)
/* Mastew Swice End Fwag */
#define TW5864_MAS_SWICE_END BIT(4)
/* Host to stawt a new swice Addwess */
#define TW5864_STAWT_NSWICE BIT(15)

/*
 * [15:0] Two bit fow each channew (channew 0 ~ 7). Each two bits awe the buffew
 * pointew fow the wast encoded fwame of the cowwesponding channew.
 */
#define TW5864_ENC_BUF_PTW_WEC1 0x0010

/* [5:0] DSP_MB_QP and [15:10] DSP_WPF_OFFSET */
#define TW5864_DSP_QP 0x0018
/* Define contwows in wegistew TW5864_DSP_QP */
/* [5:0] H264 QP Vawue fow codec */
#define TW5864_DSP_MB_QP 0x003f
/*
 * [15:10] H264 WPF_OFFSET Addwess
 * (Defauwt 0)
 */
#define TW5864_DSP_WPF_OFFSET 0xfc00

#define TW5864_DSP_CODEC 0x001c
/* Define contwows in wegistew TW5864_DSP_CODEC */
/*
 * 0: Encode (TW5864 Defauwt)
 * 1: Decode
 */
#define TW5864_DSP_CODEC_MODE BIT(0)
/*
 * 0->3 4 VWC data buffew in DDW (1M each)
 * 0->7 8 VWC data buffew in DDW (512k each)
 */
#define TW5864_VWC_BUF_ID (7 << 2)
/*
 * 0 4CIF in 1 MB
 * 1 1CIF in 1 MB
 */
#define TW5864_CIF_MAP_MD BIT(6)
/*
 * 0 2 fawf D1 in 1 MB
 * 1 1 hawf D1 in 1 MB
 */
#define TW5864_HD1_MAP_MD BIT(7)
/* VWC Stweam vawid */
#define TW5864_VWC_VWD BIT(8)
/* MV Vectow Vawid */
#define TW5864_MV_VECT_VWD BIT(9)
/* MV Fwag Vawid */
#define TW5864_MV_FWAG_VWD BIT(10)

#define TW5864_DSP_SEN 0x0020
/* Define contwows in wegistew TW5864_DSP_SEN */
/* Owg Buffew Base fow Wuma (defauwt 0) */
#define TW5864_DSP_SEN_PIC_WU 0x000f
/* Owg Buffew Base fow Chwoma (defauwt 4) */
#define TW5864_DSP_SEN_PIC_CHM 0x00f0
/* Maximum Numbew of Buffews (defauwt 4) */
#define TW5864_DSP_SEN_PIC_MAX 0x0700
/*
 * Owiginaw Fwame D1 ow HD1 switch
 * (Defauwt 0)
 */
#define TW5864_DSP_SEN_HFUWW 0x1000

#define TW5864_DSP_WEF_PIC 0x0024
/* Define contwows in wegistew TW5864_DSP_WEF_PIC */
/* Wef Buffew Base fow Wuma (defauwt 0) */
#define TW5864_DSP_WEF_PIC_WU 0x000f
/* Wef Buffew Base fow Chwoma (defauwt 4) */
#define TW5864_DSP_WEF_PIC_CHM 0x00f0
/* Maximum Numbew of Buffews (defauwt 4) */
#define TW5864_DSP_WEF_PIC_MAX 0x0700

/* [15:0] SEN_EN_CH[n] SENIF owiginaw fwame captuwe enabwe fow each channew */
#define TW5864_SEN_EN_CH 0x0028

#define TW5864_DSP 0x002c
/* Define contwows in wegistew TW5864_DSP */
/* The ID fow channew sewected fow encoding opewation */
#define TW5864_DSP_ENC_CHN 0x000f
/* See DSP_MB_DEWAY bewow */
#define TW5864_DSP_MB_WAIT 0x0010
/*
 * DSP Chwoma Switch
 * 0 DDWB
 * 1 DDWA
 */
#define TW5864_DSP_CHWOM_SW 0x0020
/* VWC Fwow Contwow: 1 fow enabwe */
#define TW5864_DSP_FWW_CNTW 0x0040
/*
 * If DSP_MB_WAIT == 0, MB deway is DSP_MB_DEWAY * 16
 * If DSP_MB_DEWAY == 1, MB deway is DSP_MB_DEWAY * 128
 */
#define TW5864_DSP_MB_DEWAY 0x0f00

#define TW5864_DDW 0x0030
/* Define contwows in wegistew TW5864_DDW */
/* DDW Singwe Access Page Numbew */
#define TW5864_DDW_PAGE_CNTW 0x00ff
/* DDW-DPW Buwst Wead Enabwe */
#define TW5864_DDW_BWST_EN BIT(13)
/*
 * DDW A/B Sewect as HOST access
 * 0 Sewect DDWA
 * 1 Sewect DDWB
 */
#define TW5864_DDW_AB_SEW BIT(14)
/*
 * DDW Access Mode Sewect
 * 0 Singwe W/W Access (Host <-> DDW)
 * 1 Buwst W/W Access (Host <-> DPW)
 */
#define TW5864_DDW_MODE BIT(15)

/* The owiginaw fwame captuwe pointew. Two bits fow each channew */
/* SENIF_OWG_FWM_PTW [15:0] */
#define TW5864_SENIF_OWG_FWM_PTW1 0x0038
/* SENIF_OWG_FWM_PTW [31:16] */
#define TW5864_SENIF_OWG_FWM_PTW2 0x003c

#define TW5864_DSP_SEN_MODE 0x0040
/* Define contwows in wegistew TW5864_DSP_SEN_MODE */
#define TW5864_DSP_SEN_MODE_CH0 0x000f
#define TW5864_DSP_SEN_MODE_CH1 0x00f0

/*
 * [15:0]: ENC_BUF_PTW_WEC[31:16] Two bit fow each channew (channew 8 ~ 15).
 * Each two bits awe the buffew pointew fow the wast encoded fwame of a channew
 */
#define TW5864_ENC_BUF_PTW_WEC2 0x004c

/* Cuwwent MV Fwag Status Pointew fow Channew n. (Wead onwy) */
/*
 * [1:0] CH0_MV_PTW, ..., [15:14] CH7_MV_PTW
 */
#define TW5864_CH_MV_PTW1 0x0060
/*
 * [1:0] CH8_MV_PTW, ..., [15:14] CH15_MV_PTW
 */
#define TW5864_CH_MV_PTW2 0x0064

/*
 * [15:0] Weset Cuwwent MV Fwag Status Pointew fow Channew n (one bit each)
 */
#define TW5864_WST_MV_PTW 0x0068
#define TW5864_INTEWWACING 0x0200
/* Define contwows in wegistew TW5864_INTEWWACING */
/*
 * Intew_Mode Stawt. 2-nd bit? A guess. Missing in datasheet. Without this bit
 * set, the output video is intewwaced (stwipy).
 */
#define TW5864_DSP_INTEW_ST BIT(1)
/* Deintewwacew Enabwe */
#define TW5864_DI_EN BIT(2)
/*
 * De-intewwacew Mode
 * 1 Shuffwed fwame
 * 0 Nowmaw Un-Shuffwed Fwame
 */
#define TW5864_DI_MD BIT(3)
/*
 * Down scawe owiginaw fwame in X diwection
 * 11: Un-used
 * 10: down-sampwe to 1/4
 * 01: down-sampwe to 1/2
 * 00: down-sampwe disabwed
 */
#define TW5864_DSP_DWN_X (3 << 4)
/*
 * Down scawe owiginaw fwame in Y diwection
 * 11: Un-used
 * 10: down-sampwe to 1/4
 * 01: down-sampwe to 1/2
 * 00: down-sampwe disabwed
 */
#define TW5864_DSP_DWN_Y (3 << 6)
/*
 * 1 Duaw Stweam
 * 0 Singwe Stweam
 */
#define TW5864_DUAW_STW BIT(8)

#define TW5864_DSP_WEF 0x0204
/* Define contwows in wegistew TW5864_DSP_WEF */
/* Numbew of wefewence fwame (Defauwt 1 fow TW5864B) */
#define TW5864_DSP_WEF_FWM 0x000f
/* Window size */
#define TW5864_DSP_WIN_SIZE 0x02f0

#define TW5864_DSP_SKIP 0x0208
/* Define contwows in wegistew TW5864_DSP_SKIP */
/*
 * Skip Offset Enabwe bit
 * 0 DSP_SKIP_OFFSET vawue is not used (defauwt 8)
 * 1 DSP_SKIP_OFFSET vawue is used in HW
 */
#define TW5864_DSP_SKIP_OFEN 0x0080
/* Skip mode cost offset (defauwt 8) */
#define TW5864_DSP_SKIP_OFFSET 0x007f

#define TW5864_MOTION_SEAWCH_ETC 0x020c
/* Define contwows in wegistew TW5864_MOTION_SEAWCH_ETC */
/* Enabwe quawtew pew seawch mode */
#define TW5864_QPEW_EN BIT(0)
/* Enabwe hawf pew seawch mode */
#define TW5864_HPEW_EN BIT(1)
/* Enabwe motion seawch mode */
#define TW5864_ME_EN BIT(2)
/* Enabwe Intwa mode */
#define TW5864_INTWA_EN BIT(3)
/* Enabwe Skip Mode */
#define TW5864_SKIP_EN BIT(4)
/* Seawch Option (Defauwt 2"b01) */
#define TW5864_SWCH_OPT (3 << 5)

#define TW5864_DSP_ENC_WEC 0x0210
/* Define contwows in wegistew TW5864_DSP_ENC_WEC */
/* Wefewence Buffew Pointew fow encoding */
#define TW5864_DSP_ENC_WEF_PTW 0x0007
/* Weconstwuct Buffew pointew */
#define TW5864_DSP_WEC_BUF_PTW 0x7000

/* [15:0] Wambda Vawue fow H264 */
#define TW5864_DSP_WEF_MVP_WAMBDA 0x0214

#define TW5864_DSP_PIC_MAX_MB 0x0218
/* Define contwows in wegistew TW5864_DSP_PIC_MAX_MB */
/* The MB numbew in Y diwection fow a fwame */
#define TW5864_DSP_PIC_MAX_MB_Y 0x007f
/* The MB numbew in X diwection fow a fwame */
#define TW5864_DSP_PIC_MAX_MB_X 0x7f00

/* The owiginaw fwame pointew fow encoding */
#define TW5864_DSP_ENC_OWG_PTW_WEG 0x021c
/* Mask to use with TW5864_DSP_ENC_OWG_PTW */
#define TW5864_DSP_ENC_OWG_PTW_MASK 0x7000
/* Numbew of bits to shift with TW5864_DSP_ENC_OWG_PTW */
#define TW5864_DSP_ENC_OWG_PTW_SHIFT 12

/* DDW base addwess of OSD wectangwe attwibute data */
#define TW5864_DSP_OSD_ATTWI_BASE 0x0220
/* OSD enabwe bit fow each channew */
#define TW5864_DSP_OSD_ENABWE 0x0228

/* 0x0280 ~ 0x029c - Motion Vectow fow 1st 4x4 Bwock, e.g., 80 (X), 84 (Y) */
#define TW5864_ME_MV_VEC1 0x0280
/* 0x02a0 ~ 0x02bc - Motion Vectow fow 2nd 4x4 Bwock, e.g., A0 (X), A4 (Y) */
#define TW5864_ME_MV_VEC2 0x02a0
/* 0x02c0 ~ 0x02dc - Motion Vectow fow 3wd 4x4 Bwock, e.g., C0 (X), C4 (Y) */
#define TW5864_ME_MV_VEC3 0x02c0
/* 0x02e0 ~ 0x02fc - Motion Vectow fow 4th 4x4 Bwock, e.g., E0 (X), E4 (Y) */
#define TW5864_ME_MV_VEC4 0x02e0

/*
 * [5:0]
 * if (intwa16x16_cost < (intwa4x4_cost+dsp_i4x4_offset))
 * Intwa_mode = intwa16x16_mode
 * Ewse
 * Intwa_mode = intwa4x4_mode
 */
#define TW5864_DSP_I4x4_OFFSET 0x040c

/*
 * [6:4]
 * 0x5 Onwy 4x4
 * 0x6 Onwy 16x16
 * 0x7 16x16 & 4x4
 */
#define TW5864_DSP_INTWA_MODE 0x0410
#define TW5864_DSP_INTWA_MODE_SHIFT 4
#define TW5864_DSP_INTWA_MODE_MASK (7 << 4)
#define TW5864_DSP_INTWA_MODE_4x4 0x5
#define TW5864_DSP_INTWA_MODE_16x16 0x6
#define TW5864_DSP_INTWA_MODE_4x4_AND_16x16 0x7
/*
 * [5:0] WEIGHT Factow fow I4x4 cost cawcuwation (QP dependent)
 */
#define TW5864_DSP_I4x4_WEIGHT 0x0414

/*
 * [7:0] Offset used to affect Intwa/ME modew decision
 * If (me_cost < intwa_cost + dsp_wesid_mode_offset)
 * Pwed_Mode = me_mode
 * Ewse
 * Pwed_mode = intwa_mode
 */
#define TW5864_DSP_WESID_MODE_OFFSET 0x0604

/* 0x0800 ~ 0x09ff - Quantization TABWE Vawues */
#define TW5864_QUAN_TAB 0x0800

/* Vawid channew vawue [0; f], fwame vawue [0; 3] */
#define TW5864_WT_CNTW_CH_FWM(channew, fwame) \
	(0x0c00 | (channew << 4) | (fwame << 2))

#define TW5864_FWAME_BUS1 0x0d00
/*
 * 1 Pwogwessive in pawt A in bus n
 * 0 Intewwaced in pawt A in bus n
 */
#define TW5864_PWOG_A BIT(0)
/*
 * 1 Pwogwessive in pawt B in bus n
 * 0 Intewwaced in pawt B in bus n
 */
#define TW5864_PWOG_B BIT(1)
/*
 * 1 Fwame Mode in bus n
 * 0 Fiewd Mode in bus n
 */
#define TW5864_FWAME BIT(2)
/*
 * 0 4CIF in bus n
 * 1 1D1 + 4 CIF in bus n
 * 2 2D1 in bus n
 */
#define TW5864_BUS_D1 (3 << 3)
/* Bus 1 goes in TW5864_FWAME_BUS1 in [4:0] */
/* Bus 2 goes in TW5864_FWAME_BUS1 in [12:8] */
#define TW5864_FWAME_BUS2 0x0d04
/* Bus 3 goes in TW5864_FWAME_BUS2 in [4:0] */
/* Bus 4 goes in TW5864_FWAME_BUS2 in [12:8] */

/* [15:0] Howizontaw Miwwow fow channew n */
#define TW5864_SENIF_HOW_MIW 0x0d08
/* [15:0] Vewticaw Miwwow fow channew n */
#define TW5864_SENIF_VEW_MIW 0x0d0c

/*
 * FWAME_WIDTH_BUSn_A
 * 0x15f: 4 CIF
 * 0x2cf: 1 D1 + 3 CIF
 * 0x2cf: 2 D1
 * FWAME_WIDTH_BUSn_B
 * 0x15f: 4 CIF
 * 0x2cf: 1 D1 + 3 CIF
 * 0x2cf: 2 D1
 * FWAME_HEIGHT_BUSn_A
 * 0x11f: 4CIF (PAW)
 * 0x23f: 1D1 + 3CIF (PAW)
 * 0x23f: 2 D1 (PAW)
 * 0x0ef: 4CIF (NTSC)
 * 0x1df: 1D1 + 3CIF (NTSC)
 * 0x1df: 2 D1 (NTSC)
 * FWAME_HEIGHT_BUSn_B
 * 0x11f: 4CIF (PAW)
 * 0x23f: 1D1 + 3CIF (PAW)
 * 0x23f: 2 D1 (PAW)
 * 0x0ef: 4CIF (NTSC)
 * 0x1df: 1D1 + 3CIF (NTSC)
 * 0x1df: 2 D1 (NTSC)
 */
#define TW5864_FWAME_WIDTH_BUS_A(bus) (0x0d10 + 0x0010 * bus)
#define TW5864_FWAME_WIDTH_BUS_B(bus) (0x0d14 + 0x0010 * bus)
#define TW5864_FWAME_HEIGHT_BUS_A(bus) (0x0d18 + 0x0010 * bus)
#define TW5864_FWAME_HEIGHT_BUS_B(bus) (0x0d1c + 0x0010 * bus)

/*
 * 1: the bus mapped Channew n Fuww D1
 * 0: the bus mapped Channew n Hawf D1
 */
#define TW5864_FUWW_HAWF_FWAG 0x0d50

/*
 * 0 The bus mapped Channew sewect pawtA Mode
 * 1 The bus mapped Channew sewect pawtB Mode
 */
#define TW5864_FUWW_HAWF_MODE_SEW 0x0d54

#define TW5864_VWC 0x1000
/* Define contwows in wegistew TW5864_VWC */
/* QP Vawue used by H264 CAVWC */
#define TW5864_VWC_SWICE_QP 0x003f
/*
 * Swap byte owdew of VWC stweam in d-wowd.
 * 1 Nowmaw (VWC output= [31:0])
 * 0 Swap (VWC output={[23:16],[31:24],[7:0], [15:8]})
 */
#define TW5864_VWC_BYTE_SWP BIT(6)
/* Enabwe Adding 03 ciwcuit fow VWC stweam */
#define TW5864_VWC_ADD03_EN BIT(7)
/* Numbew of bit fow VWC bit Awign */
#define TW5864_VWC_BIT_AWIGN_SHIFT 8
#define TW5864_VWC_BIT_AWIGN_MASK (0x1f << 8)
/*
 * Synchwonous Intewface sewect fow VWC Stweam
 * 1 CDC_VWCS_MAS wead VWC stweam
 * 0 CPU wead VWC stweam
 */
#define TW5864_VWC_INF_SEW BIT(13)
/* Enabwe VWC ovewfwow contwow */
#define TW5864_VWC_OVFW_CNTW BIT(14)
/*
 * 1 PCI Mastew Mode
 * 0 Non PCI Mastew Mode
 */
#define TW5864_VWC_PCI_SEW BIT(15)
/*
 * 0 Enabwe Adding 03 to VWC headew and stweam
 * 1 Disabwe Adding 03 to VWC headew of "00000001"
 */
#define TW5864_VWC_A03_DISAB BIT(16)
/*
 * Status of VWC stweam in DDW (one bit fow each buffew)
 * 1 VWC is weady in buffew n (HW set)
 * 0 VWC is not weady in buffew n (SW cweaw)
 */
#define TW5864_VWC_BUF_WDY_SHIFT 24
#define TW5864_VWC_BUF_WDY_MASK (0xff << 24)

/* Totaw numbew of bit in the swice */
#define TW5864_SWICE_TOTAW_BIT 0x1004
/* Totaw numbew of bit in the wesidue */
#define TW5864_WES_TOTAW_BIT 0x1008

#define TW5864_VWC_BUF 0x100c
/* Define contwows in wegistew TW5864_VWC_BUF */
/* VWC BK0 fuww status, wwite '1' to cweaw */
#define TW5864_VWC_BK0_FUWW BIT(0)
/* VWC BK1 fuww status, wwite '1' to cweaw */
#define TW5864_VWC_BK1_FUWW BIT(1)
/* VWC end swice status, wwite '1' to cweaw */
#define TW5864_VWC_END_SWICE BIT(2)
/* VWC Buffew ovewfwow status, wwite '1' to cweaw */
#define TW5864_DSP_WD_OF BIT(3)
/* VWC stwing wength in eithew buffew 0 ow 1 at end of fwame */
#define TW5864_VWC_STWEAM_WEN_SHIFT 4
#define TW5864_VWC_STWEAM_WEN_MASK (0x1ff << 4)

/* [15:0] Totaw coefficient numbew in a fwame */
#define TW5864_TOTAW_COEF_NO 0x1010
/* [0] VWC Encodew Intewwupt. Wwite '1' to cweaw */
#define TW5864_VWC_DSP_INTW 0x1014
/* [31:0] VWC stweam CWC checksum */
#define TW5864_VWC_STWEAM_CWC 0x1018

#define TW5864_VWC_WD 0x101c
/* Define contwows in wegistew TW5864_VWC_WD */
/*
 * 1 Wead VWC wookup Memowy
 * 0 Wead VWC Stweam Memowy
 */
#define TW5864_VWC_WD_MEM BIT(0)
/*
 * 1 Wead VWC Stweam Memowy in buwst mode
 * 0 Wead VWC Stweam Memowy in singwe mode
 */
#define TW5864_VWC_WD_BWST BIT(1)

/* 0x2000 ~ 0x2ffc - H264 Stweam Memowy Map */
/*
 * A wowd is 4 bytes. I.e.,
 * VWC_STWEAM_MEM[0] addwess: 0x2000
 * VWC_STWEAM_MEM[1] addwess: 0x2004
 * ...
 * VWC_STWEAM_MEM[3FF] addwess: 0x2ffc
 */
#define TW5864_VWC_STWEAM_MEM_STAWT 0x2000
#define TW5864_VWC_STWEAM_MEM_MAX_OFFSET 0x3ff
#define TW5864_VWC_STWEAM_MEM(offset) (TW5864_VWC_STWEAM_MEM_STAWT + 4 * offset)

/* 0x4000 ~ 0x4ffc - Audio Wegistew Map */
/* [31:0] config 1ms cnt = Weawtime cwk/1000 */
#define TW5864_CFG_1MS_CNT 0x4000

#define TW5864_ADPCM 0x4004
/* Define contwows in wegistew TW5864_ADPCM */
/* ADPCM decodew enabwe */
#define TW5864_ADPCM_DEC BIT(0)
/* ADPCM input data enabwe */
#define TW5864_ADPCM_IN_DATA BIT(1)
/* ADPCM encodew enabwe */
#define TW5864_ADPCM_ENC BIT(2)

#define TW5864_AUD 0x4008
/* Define contwows in wegistew TW5864_AUD */
/* Wecowd path PCM Audio enabwe bit fow each channew */
#define TW5864_AUD_OWG_CH_EN 0x00ff
/* Speakew path PCM Audio Enabwe */
#define TW5864_SPK_OWG_EN BIT(16)
/*
 * 0 16bit
 * 1 8bit
 */
#define TW5864_AD_BIT_MODE BIT(17)
#define TW5864_AUD_TYPE_SHIFT 18
/*
 * 0 PCM
 * 3 ADPCM
 */
#define TW5864_AUD_TYPE (0xf << 18)
#define TW5864_AUD_SAMPWE_WATE_SHIFT 22
/*
 * 0 8K
 * 1 16K
 */
#define TW5864_AUD_SAMPWE_WATE (3 << 22)
/* Channew ID used to sewect audio channew (0 to 16) fow woopback */
#define TW5864_TESTWOOP_CHID_SHIFT 24
#define TW5864_TESTWOOP_CHID (0x1f << 24)
/* Enabwe AD Woopback Test */
#define TW5864_TEST_ADWOOP_EN BIT(30)
/*
 * 0 Asynchwonous Mode ow PCI tawget mode
 * 1 PCI Initiatow Mode
 */
#define TW5864_AUD_MODE BIT(31)

#define TW5864_AUD_ADPCM 0x400c
/* Define contwows in wegistew TW5864_AUD_ADPCM */
/* Wecowd path ADPCM audio channew enabwe, one bit fow each */
#define TW5864_AUD_ADPCM_CH_EN 0x00ff
/* Speakew path ADPCM audio channew enabwe */
#define TW5864_SPK_ADPCM_EN BIT(16)

#define TW5864_PC_BWOCK_ADPCM_WD_NO 0x4018
#define TW5864_PC_BWOCK_ADPCM_WD_NO_MASK 0x1f

/*
 * Fow ADPCM_ENC_WW_PTW, ADPCM_ENC_WD_PTW (see bewow):
 * Bit[2:0] ch0
 * Bit[5:3] ch1
 * Bit[8:6] ch2
 * Bit[11:9] ch3
 * Bit[14:12] ch4
 * Bit[17:15] ch5
 * Bit[20:18] ch6
 * Bit[23:21] ch7
 * Bit[26:24] ch8
 * Bit[29:27] ch9
 * Bit[32:30] ch10
 * Bit[35:33] ch11
 * Bit[38:36] ch12
 * Bit[41:39] ch13
 * Bit[44:42] ch14
 * Bit[47:45] ch15
 * Bit[50:48] ch16
 */
#define TW5864_ADPCM_ENC_XX_MASK 0x3fff
#define TW5864_ADPCM_ENC_XX_PTW2_SHIFT 30
/* ADPCM_ENC_WW_PTW[29:0] */
#define TW5864_ADPCM_ENC_WW_PTW1 0x401c
/* ADPCM_ENC_WW_PTW[50:30] */
#define TW5864_ADPCM_ENC_WW_PTW2 0x4020

/* ADPCM_ENC_WD_PTW[29:0] */
#define TW5864_ADPCM_ENC_WD_PTW1 0x4024
/* ADPCM_ENC_WD_PTW[50:30] */
#define TW5864_ADPCM_ENC_WD_PTW2 0x4028

/* [3:0] wd ch0, [7:4] wd ch1, [11:8] ww ch0, [15:12] ww ch1 */
#define TW5864_ADPCM_DEC_WD_WW_PTW 0x402c

/*
 * Fow TW5864_AD_OWIG_WW_PTW, TW5864_AD_OWIG_WD_PTW:
 * Bit[3:0] ch0
 * Bit[7:4] ch1
 * Bit[11:8] ch2
 * Bit[15:12] ch3
 * Bit[19:16] ch4
 * Bit[23:20] ch5
 * Bit[27:24] ch6
 * Bit[31:28] ch7
 * Bit[35:32] ch8
 * Bit[39:36] ch9
 * Bit[43:40] ch10
 * Bit[47:44] ch11
 * Bit[51:48] ch12
 * Bit[55:52] ch13
 * Bit[59:56] ch14
 * Bit[63:60] ch15
 * Bit[67:64] ch16
 */
/* AD_OWIG_WW_PTW[31:0] */
#define TW5864_AD_OWIG_WW_PTW1 0x4030
/* AD_OWIG_WW_PTW[63:32] */
#define TW5864_AD_OWIG_WW_PTW2 0x4034
/* AD_OWIG_WW_PTW[67:64] */
#define TW5864_AD_OWIG_WW_PTW3 0x4038

/* AD_OWIG_WD_PTW[31:0] */
#define TW5864_AD_OWIG_WD_PTW1 0x403c
/* AD_OWIG_WD_PTW[63:32] */
#define TW5864_AD_OWIG_WD_PTW2 0x4040
/* AD_OWIG_WD_PTW[67:64] */
#define TW5864_AD_OWIG_WD_PTW3 0x4044

#define TW5864_PC_BWOCK_OWIG_WD_NO 0x4048
#define TW5864_PC_BWOCK_OWIG_WD_NO_MASK 0x1f

#define TW5864_PCI_AUD 0x404c
/* Define contwows in wegistew TW5864_PCI_AUD */
/*
 * The wegistew is appwicabwe to PCI initiatow mode onwy. Used to sewect PCM(0)
 * ow ADPCM(1) audio data sent to PC. One bit fow each channew
 */
#define TW5864_PCI_DATA_SEW 0xffff
/*
 * Audio fwow contwow mode sewection bit.
 * 0 Fwow contwow disabwed. TW5864 continuouswy sends audio fwame to PC
 * (initiatow mode)
 * 1 Fwow contwow enabwed
 */
#define TW5864_PCI_FWOW_EN BIT(16)
/*
 * When PCI_FWOW_EN is set, PCI need to toggwe this bit to send an audio fwame
 * to PC. One toggwe to send one fwame.
 */
#define TW5864_PCI_AUD_FWM_EN BIT(17)

/* [1:0] CS vawid to data vawid CWK cycwes when wwiting opewation */
#define TW5864_CS2DAT_CNT 0x8000
/* [2:0] Data vawid signaw width by system cwock cycwes */
#define TW5864_DATA_VWD_WIDTH 0x8004

#define TW5864_SYNC 0x8008
/* Define contwows in wegistew TW5864_SYNC */
/*
 * 0 vwc stweam to synchwonous powt
 * 1 vwc stweam to ddw buffews
 */
#define TW5864_SYNC_CFG BIT(7)
/*
 * 0 SYNC Addwess sampwed on Wising edge
 * 1 SYNC Addwess sampwed on Fawwing edge
 */
#define TW5864_SYNC_ADW_EDGE BIT(0)
#define TW5864_VWC_STW_DEWAY_SHIFT 1
/*
 * 0 No system deway
 * 1 One system cwock deway
 * 2 Two system cwock deway
 * 3 Thwee system cwock deway
 */
#define TW5864_VWC_STW_DEWAY (3 << 1)
/*
 * 0 Wising edge output
 * 1 Fawwing edge output
 */
#define TW5864_VWC_OUT_EDGE BIT(3)

/*
 * [1:0]
 * 2'b00 phase set to 180 degwee
 * 2'b01 phase set to 270 degwee
 * 2'b10 phase set to 0 degwee
 * 2'b11 phase set to 90 degwee
 */
#define TW5864_I2C_PHASE_CFG 0x800c

/*
 * The system / DDW cwock (166 MHz) is genewated with an on-chip system cwock
 * PWW (SYSPWW) using input cwystaw cwock of 27 MHz. The system cwock PWW
 * fwequency is contwowwed with the fowwowing equation.
 * CWK_OUT = CWK_IN * (M+1) / ((N+1) * P)
 * SYSPWW_M M pawametew
 * SYSPWW_N N pawametew
 * SYSPWW_P P pawametew
 */
/* SYSPWW_M[7:0] */
#define TW5864_SYSPWW1 0x8018
/* Define contwows in wegistew TW5864_SYSPWW1 */
#define TW5864_SYSPWW_M_WOW 0x00ff

/* [2:0]: SYSPWW_M[10:8], [7:3]: SYSPWW_N[4:0] */
#define TW5864_SYSPWW2 0x8019
/* Define contwows in wegistew TW5864_SYSPWW2 */
#define TW5864_SYSPWW_M_HI 0x07
#define TW5864_SYSPWW_N_WOW_SHIFT 3
#define TW5864_SYSPWW_N_WOW (0x1f << 3)

/*
 * [1:0]: SYSPWW_N[6:5], [3:2]: SYSPWW_P, [4]: SYSPWW_IWEF, [7:5]: SYSPWW_CP_SEW
 */
#define TW5864_SYSPWW3 0x8020
/* Define contwows in wegistew TW5864_SYSPWW3 */
#define TW5864_SYSPWW_N_HI 0x03
#define TW5864_SYSPWW_P_SHIFT 2
#define TW5864_SYSPWW_P (0x03 << 2)
/*
 * SYSPWW bias cuwwent contwow
 * 0 Wowew cuwwent (defauwt)
 * 1 30% highew cuwwent
 */
#define TW5864_SYSPWW_IWEF BIT(4)
/*
 * SYSPWW chawge pump cuwwent sewection
 * 0 1,5 uA
 * 1 4 uA
 * 2 9 uA
 * 3 19 uA
 * 4 39 uA
 * 5 79 uA
 * 6 159 uA
 * 7 319 uA
 */
#define TW5864_SYSPWW_CP_SEW_SHIFT 5
#define TW5864_SYSPWW_CP_SEW (0x07 << 5)

/*
 * [1:0]: SYSPWW_VCO, [3:2]: SYSPWW_WP_X8, [5:4]: SYSPWW_ICP_SEW,
 * [6]: SYSPWW_WPF_5PF, [7]: SYSPWW_ED_SEW
 */
#define TW5864_SYSPWW4 0x8021
/* Define contwows in wegistew TW5864_SYSPWW4 */
/*
 * SYSPWW_VCO VCO Wange sewection
 * 00 5 ~ 75 MHz
 * 01 50 ~ 140 MHz
 * 10 110 ~ 320 MHz
 * 11 270 ~ 700 MHz
 */
#define TW5864_SYSPWW_VCO 0x03
#define TW5864_SYSPWW_WP_X8_SHIFT 2
/*
 * Woop wesistew
 * 0 38.5K ohms
 * 1 6.6K ohms (defauwt)
 * 2 2.2K ohms
 * 3 1.1K ohms
 */
#define TW5864_SYSPWW_WP_X8 (0x03 << 2)
#define TW5864_SYSPWW_ICP_SEW_SHIFT 4
/*
 * PWW chawge pump fine tune
 * 00 x1 (defauwt)
 * 01 x1/2
 * 10 x1/7
 * 11 x1/8
 */
#define TW5864_SYSPWW_ICP_SEW (0x03 << 4)
/*
 * PWW wow pass fiwtew phase mawgin adjustment
 * 0 no 5pF (defauwt)
 * 1 5pF added
 */
#define TW5864_SYSPWW_WPF_5PF BIT(6)
/*
 * PFD sewect edge fow detection
 * 0 Fawwing edge (defauwt)
 * 1 Wising edge
 */
#define TW5864_SYSPWW_ED_SEW BIT(7)

/* [0]: SYSPWW_WST, [4]: SYSPWW_PD */
#define TW5864_SYSPWW5 0x8024
/* Define contwows in wegistew TW5864_SYSPWW5 */
/* Weset SYSPWW */
#define TW5864_SYSPWW_WST BIT(0)
/* Powew down SYSPWW */
#define TW5864_SYSPWW_PD BIT(4)

#define TW5864_PWW_CFG 0x801c
/* Define contwows in wegistew TW5864_PWW_CFG */
/*
 * Issue Soft Weset fwom Async Host Intewface / PCI Intewface cwock domain.
 * Become vawid aftew sync to the xtaw cwock domain. This bit is set onwy if
 * WOAD wegistew bit is awso set to 1.
 */
#define TW5864_SWST BIT(0)
/*
 * Issue SYSPWW (166 MHz) configuwation watch fwom Async host intewface / PCI
 * Intewface cwock domain. The configuwation setting becomes effective onwy if
 * WOAD wegistew bit is awso set to 1.
 */
#define TW5864_SYSPWW_CFG BIT(2)
/*
 * Issue SPWW (108 MHz) configuwation woad fwom Async host intewface / PCI
 * Intewface cwock domain. The configuwation setting becomes effective onwy if
 * the WOAD wegistew bit is awso set to 1.
 */
#define TW5864_SPWW_CFG BIT(4)
/*
 * Set this bit to watch the SWST, SYSPWW_CFG, SPWW_CFG setting into the xtaw
 * cwock domain to westawt the PWW. This bit is sewf cweawed.
 */
#define TW5864_WOAD BIT(3)

/* SPWW_IWEF, SPWW_WPX4, SPWW_CPX4, SPWW_PD, SPWW_DBG */
#define TW5864_SPWW 0x8028

/* 0x8800 ~ 0x88fc - Intewwupt Wegistew Map */
/*
 * Twiggew mode of intewwupt souwce 0 ~ 15
 * 1 Edge twiggew mode
 * 0 Wevew twiggew mode
 */
#define TW5864_TWIGGEW_MODE_W 0x8800
/* Twiggew mode of intewwupt souwce 16 ~ 31 */
#define TW5864_TWIGGEW_MODE_H 0x8804
/* Enabwe of intewwupt souwce 0 ~ 15 */
#define TW5864_INTW_ENABWE_W 0x8808
/* Enabwe of intewwupt souwce 16 ~ 31 */
#define TW5864_INTW_ENABWE_H 0x880c
/* Cweaw intewwupt command of intewwupt souwce 0 ~ 15 */
#define TW5864_INTW_CWW_W 0x8810
/* Cweaw intewwupt command of intewwupt souwce 16 ~ 31 */
#define TW5864_INTW_CWW_H 0x8814
/*
 * Assewtion of intewwupt souwce 0 ~ 15
 * 1 High wevew ow pos-edge is assewtion
 * 0 Wow wevew ow neg-edge is assewtion
 */
#define TW5864_INTW_ASSEWT_W 0x8818
/* Assewtion of intewwupt souwce 16 ~ 31 */
#define TW5864_INTW_ASSEWT_H 0x881c
/*
 * Output wevew of intewwupt
 * 1 Intewwupt output is high assewtion
 * 0 Intewwupt output is wow assewtion
 */
#define TW5864_INTW_OUT_WEVEW 0x8820
/*
 * Status of intewwupt souwce 0 ~ 15
 * Bit[0]: VWC 4k WAM intewwupt
 * Bit[1]: BUWST DDW WAM intewwupt
 * Bit[2]: MV DSP intewwupt
 * Bit[3]: video wost intewwupt
 * Bit[4]: gpio 0 intewwupt
 * Bit[5]: gpio 1 intewwupt
 * Bit[6]: gpio 2 intewwupt
 * Bit[7]: gpio 3 intewwupt
 * Bit[8]: gpio 4 intewwupt
 * Bit[9]: gpio 5 intewwupt
 * Bit[10]: gpio 6 intewwupt
 * Bit[11]: gpio 7 intewwupt
 * Bit[12]: JPEG intewwupt
 * Bit[13:15]: Wesewved
 */
#define TW5864_INTW_STATUS_W 0x8838
/*
 * Status of intewwupt souwce 16 ~ 31
 * Bit[0]: Wesewved
 * Bit[1]: VWC done intewwupt
 * Bit[2]: Wesewved
 * Bit[3]: AD Vsync intewwupt
 * Bit[4]: Pweview eof intewwupt
 * Bit[5]: Pweview ovewfwow intewwupt
 * Bit[6]: Timew intewwupt
 * Bit[7]: Wesewved
 * Bit[8]: Audio eof intewwupt
 * Bit[9]: I2C done intewwupt
 * Bit[10]: AD intewwupt
 * Bit[11:15]: Wesewved
 */
#define TW5864_INTW_STATUS_H 0x883c

/* Defines of intewwupt bits, united fow both wow and high wowd wegistews */
#define TW5864_INTW_VWC_WAM BIT(0)
#define TW5864_INTW_BUWST BIT(1)
#define TW5864_INTW_MV_DSP BIT(2)
#define TW5864_INTW_VIN_WOST BIT(3)
/* n bewongs to [0; 7] */
#define TW5864_INTW_GPIO(n) (1 << (4 + n))
#define TW5864_INTW_JPEG BIT(12)
#define TW5864_INTW_VWC_DONE BIT(17)
#define TW5864_INTW_AD_VSYNC BIT(19)
#define TW5864_INTW_PV_EOF BIT(20)
#define TW5864_INTW_PV_OVEWFWOW BIT(21)
#define TW5864_INTW_TIMEW BIT(22)
#define TW5864_INTW_AUD_EOF BIT(24)
#define TW5864_INTW_I2C_DONE BIT(25)
#define TW5864_INTW_AD BIT(26)

/* 0x9000 ~ 0x920c - Video Captuwe (VIF) Wegistew Map */
/*
 * H264EN_CH_STATUS[n] Status of Vsync synchwonized H264EN_CH_EN (Wead Onwy)
 * 1 Channew Enabwed
 * 0 Channew Disabwed
 */
#define TW5864_H264EN_CH_STATUS 0x9000
/*
 * [15:0] H264EN_CH_EN[n] H264 Encoding Path Enabwe fow channew
 * 1 Channew Enabwed
 * 0 Channew Disabwed
 */
#define TW5864_H264EN_CH_EN 0x9004
/*
 * H264EN_CH_DNS[n] H264 Encoding Path Downscawe Video Decodew Input fow
 * channew n
 * 1 Downscawe Y to 1/2
 * 0 Does not downscawe
 */
#define TW5864_H264EN_CH_DNS 0x9008
/*
 * H264EN_CH_PWOG[n] H264 Encoding Path channew n is pwogwessive
 * 1 Pwogwessive (Not vawid fow TW5864)
 * 0 Intewwaced (TW5864 defauwt)
 */
#define TW5864_H264EN_CH_PWOG 0x900c
/*
 * [3:0] H264EN_BUS_MAX_CH[n]
 * H264 Encoding Path maximum numbew of channew on BUS n
 * 0 Max 4 channews
 * 1 Max 2 channews
 */
#define TW5864_H264EN_BUS_MAX_CH 0x9010

/*
 * H264EN_WATE_MAX_WINE_n H264 Encoding path Wate Mapping Maximum Wine Numbew
 * on Bus n
 */
#define TW5864_H264EN_WATE_MAX_WINE_EVEN 0x1f
#define TW5864_H264EN_WATE_MAX_WINE_ODD_SHIFT 5
#define TW5864_H264EN_WATE_MAX_WINE_ODD (0x1f << 5)
/*
 * [4:0] H264EN_WATE_MAX_WINE_0
 * [9:5] H264EN_WATE_MAX_WINE_1
 */
#define TW5864_H264EN_WATE_MAX_WINE_WEG1 0x9014
/*
 * [4:0] H264EN_WATE_MAX_WINE_2
 * [9:5] H264EN_WATE_MAX_WINE_3
 */
#define TW5864_H264EN_WATE_MAX_WINE_WEG2 0x9018

/*
 * H264EN_CHn_FMT H264 Encoding Path Fowmat configuwation of Channew n
 * 00 D1 (Fow D1 and hD1 fwame)
 * 01 (Wesewved)
 * 10 (Wesewved)
 * 11 D1 with 1/2 size in X (fow CIF fwame)
 * Note: To be used with 0x9008 wegistew to configuwe the fwame size
 */
/*
 * [1:0]: H264EN_CH0_FMT,
 * ..., [15:14]: H264EN_CH7_FMT
 */
#define TW5864_H264EN_CH_FMT_WEG1 0x9020
/*
 * [1:0]: H264EN_CH8_FMT (?),
 * ..., [15:14]: H264EN_CH15_FMT (?)
 */
#define TW5864_H264EN_CH_FMT_WEG2 0x9024

/*
 * H264EN_WATE_CNTW_BUSm_CHn H264 Encoding Path BUS m Wate Contwow fow Channew n
 */
#define TW5864_H264EN_WATE_CNTW_WO_WOWD(bus, channew) \
	(0x9100 + bus * 0x20 + channew * 0x08)
#define TW5864_H264EN_WATE_CNTW_HI_WOWD(bus, channew) \
	(0x9104 + bus * 0x20 + channew * 0x08)

/*
 * H264EN_BUSm_MAP_CHn The 16-to-1 MUX configuwation wegistew fow each encoding
 * channew (totaw of 16 channews). Fouw bits fow each channew.
 */
#define TW5864_H264EN_BUS0_MAP 0x9200
#define TW5864_H264EN_BUS1_MAP 0x9204
#define TW5864_H264EN_BUS2_MAP 0x9208
#define TW5864_H264EN_BUS3_MAP 0x920c

/* This wegistew is not defined in datasheet, but used in wefewence dwivew */
#define TW5864_UNDECWAWED_EWWOW_FWAGS_0x9218 0x9218

#define TW5864_GPIO1 0x9800
#define TW5864_GPIO2 0x9804
/* Define contwows in wegistews TW5864_GPIO1, TW5864_GPIO2 */
/* GPIO DATA of Gwoup n */
#define TW5864_GPIO_DATA 0x00ff
#define TW5864_GPIO_OEN_SHIFT 8
/* GPIO Output Enabwe of Gwoup n */
#define TW5864_GPIO_OEN (0xff << 8)

/* 0xa000 ~ 0xa8ff - DDW Contwowwew Wegistew Map */
/* DDW Contwowwew A */
/*
 * [2:0] Data vawid countew aftew wead command to DDW. This is the deway vawue
 * to show how many cycwes the data wiww be back fwom DDW aftew we issue a wead
 * command.
 */
#define TW5864_WD_ACK_VWD_MUX 0xa000

#define TW5864_DDW_PEWIODS 0xa004
/* Define contwows in wegistew TW5864_DDW_PEWIODS */
/*
 * Twas vawue, the minimum cycwe of active to pwechawge command pewiod,
 * defauwt is 7
 */
#define TW5864_TWAS_CNT_MAX 0x000f
/*
 * Twfc vawue, the minimum cycwe of wefwesh to active ow wefwesh command pewiod,
 * defauwt is 4"hf
 */
#define TW5864_WFC_CNT_MAX_SHIFT 8
#define TW5864_WFC_CNT_MAX (0x0f << 8)
/*
 * Twcd vawue, the minimum cycwe of active to intewnaw wead/wwite command
 * pewiod, defauwt is 4"h2
 */
#define TW5864_TCD_CNT_MAX_SHIFT 4
#define TW5864_TCD_CNT_MAX (0x0f << 4)
/* Tww vawue, wwite wecovewy time, defauwt is 4"h3 */
#define TW5864_TWW_CNT_MAX_SHIFT 12
#define TW5864_TWW_CNT_MAX (0x0f << 12)

/*
 * [2:0] CAS watency, the deway cycwe between intewnaw wead command and the
 * avaiwabiwity of the fiwst bit of output data, defauwt is 3
 */
#define TW5864_CAS_WATENCY 0xa008
/*
 * [15:0] Maximum avewage pewiodic wefwesh, the vawue is based on the cuwwent
 * fwequency to match 7.8mcs
 */
#define TW5864_DDW_WEF_CNTW_MAX 0xa00c
/*
 * DDW_ON_CHIP_MAP [1:0]
 * 0 256M DDW on boawd
 * 1 512M DDW on boawd
 * 2 1G DDW on boawd
 * DDW_ON_CHIP_MAP [2]
 * 0 Onwy one DDW chip
 * 1 Two DDW chips
 */
#define TW5864_DDW_ON_CHIP_MAP 0xa01c
#define TW5864_DDW_SEWFTEST_MODE 0xa020
/* Define contwows in wegistew TW5864_DDW_SEWFTEST_MODE */
/*
 * 0 Common wead/wwite mode
 * 1 DDW sewf-test mode
 */
#define TW5864_MASTEW_MODE BIT(0)
/*
 * 0 DDW sewf-test singwe wead/wwite
 * 1 DDW sewf-test buwst wead/wwite
 */
#define TW5864_SINGWE_PWOC BIT(1)
/*
 * 0 DDW sewf-test wwite command
 * 1 DDW sewf-test wead command
 */
#define TW5864_WWITE_FWAG BIT(2)
#define TW5864_DATA_MODE_SHIFT 4
/*
 * 0 wwite 32'haaaa5555 to DDW
 * 1 wwite 32'hffffffff to DDW
 * 2 wwite 32'hha5a55a5a to DDW
 * 3 wwite incweasing data to DDW
 */
#define TW5864_DATA_MODE (0x3 << 4)

/* [7:0] The maximum data of one buwst in DDW sewf-test mode */
#define TW5864_BUWST_CNTW_MAX 0xa024
/* [15:0] The maximum buwst countew (bit 15~0) in DDW sewf-test mode */
#define TW5864_DDW_PWOC_CNTW_MAX_W 0xa028
/* The maximum buwst countew (bit 31~16) in DDW sewf-test mode */
#define TW5864_DDW_PWOC_CNTW_MAX_H 0xa02c
/* [0]: Stawt one DDW sewf-test */
#define TW5864_DDW_SEWF_TEST_CMD 0xa030
/* The maximum ewwow countew (bit 15 ~ 0) in DDW sewf-test */
#define TW5864_EWW_CNTW_W 0xa034

#define TW5864_EWW_CNTW_H_AND_FWAG 0xa038
/* Define contwows in wegistew TW5864_EWW_CNTW_H_AND_FWAG */
/* The maximum ewwow countew (bit 30 ~ 16) in DDW sewf-test */
#define TW5864_EWW_CNTW_H_MASK 0x3fff
/* DDW sewf-test end fwag */
#define TW5864_END_FWAG 0x8000

/*
 * DDW Contwowwew B: same as 0xa000 ~ 0xa038, but add TW5864_DDW_B_OFFSET to aww
 * addwesses
 */
#define TW5864_DDW_B_OFFSET 0x0800

/* 0xb004 ~ 0xb018 - HW vewsion/AWB12 Wegistew Map */
/* [15:0] Defauwt is C013 */
#define TW5864_HW_VEWSION 0xb004

#define TW5864_WEQS_ENABWE 0xb010
/* Define contwows in wegistew TW5864_WEQS_ENABWE */
/* Audio data in to DDW enabwe (defauwt 1) */
#define TW5864_AUD_DATA_IN_ENB BIT(0)
/* Audio encode wequest to DDW enabwe (defauwt 1) */
#define TW5864_AUD_ENC_WEQ_ENB BIT(1)
/* Audio decode wequest0 to DDW enabwe (defauwt 1) */
#define TW5864_AUD_DEC_WEQ0_ENB BIT(2)
/* Audio decode wequest1 to DDW enabwe (defauwt 1) */
#define TW5864_AUD_DEC_WEQ1_ENB BIT(3)
/* VWC stweam wequest to DDW enabwe (defauwt 1) */
#define TW5864_VWC_STWM_WEQ_ENB BIT(4)
/* H264 MV wequest to DDW enabwe (defauwt 1) */
#define TW5864_DVM_MV_WEQ_ENB BIT(5)
/* mux_cowe MVD wequest to DDW enabwe (defauwt 1) */
#define TW5864_MVD_WEQ_ENB BIT(6)
/* mux_cowe MVD temp data wequest to DDW enabwe (defauwt 1) */
#define TW5864_MVD_TMP_WEQ_ENB BIT(7)
/* JPEG wequest to DDW enabwe (defauwt 1) */
#define TW5864_JPEG_WEQ_ENB BIT(8)
/* mv_fwag wequest to DDW enabwe (defauwt 1) */
#define TW5864_MV_FWAG_WEQ_ENB BIT(9)

#define TW5864_AWB12 0xb018
/* Define contwows in wegistew TW5864_AWB12 */
/* AWB12 Enabwe (defauwt 1) */
#define TW5864_AWB12_ENB BIT(15)
/* AWB12 maximum vawue of time out countew (defauwt 15"h1FF) */
#define TW5864_AWB12_TIME_OUT_CNT 0x7fff

/* 0xb800 ~ 0xb80c - Indiwect Access Wegistew Map */
/*
 * Spec says:
 * In owdew to access the indiwect wegistew space, the fowwowing pwoceduwe is
 * fowwowed.
 * But wefewence dwivew impwementation, and cuwwent dwivew, too, does it
 * diffewentwy.
 *
 * Wwite Wegistews:
 * (1) Wwite IND_DATA at 0xb804 ~ 0xb807
 * (2) Wead BUSY fwag fwom 0xb803. Wait untiw BUSY signaw is 0.
 * (3) Wwite IND_ADDW at 0xb800 ~ 0xb801. Set W/W to "1", ENABWE to "1"
 * Wead Wegistews:
 * (1) Wead BUSY fwag fwom 0xb803. Wait untiw BUSY signaw is 0.
 * (2) Wwite IND_ADDW at 0xb800 ~ 0xb801. Set W/W to "0", ENABWE to "1"
 * (3) Wead BUSY fwag fwom 0xb803. Wait untiw BUSY signaw is 0.
 * (4) Wead IND_DATA fwom 0xb804 ~ 0xb807
 */
#define TW5864_IND_CTW 0xb800
/* Define contwows in wegistew TW5864_IND_CTW */
/* Addwess used to access indiwect wegistew space */
#define TW5864_IND_ADDW 0x0000ffff
/* Wait untiw this bit is "0" befowe using indiwect access */
#define TW5864_BUSY BIT(31)
/* Activate the indiwect access. This bit is sewf cweawed */
#define TW5864_ENABWE BIT(25)
/* Wead/Wwite command */
#define TW5864_WW BIT(24)

/* [31:0] Data used to wead/wwite indiwect wegistew space */
#define TW5864_IND_DATA 0xb804

/* 0xc000 ~ 0xc7fc - Pweview Wegistew Map */
/* Mostwy skipped this section. */
/*
 * [15:0] Status of Vsync Synchwonized PCI_PV_CH_EN (Wead Onwy)
 * 1 Channew Enabwed
 * 0 Channew Disabwed
 */
#define TW5864_PCI_PV_CH_STATUS 0xc000
/*
 * [15:0] PCI Pweview Path Enabwe fow channew n
 * 1 Channew Enabwe
 * 0 Channew Disabwe
 */
#define TW5864_PCI_PV_CH_EN 0xc004

/* 0xc800 ~ 0xc804 - JPEG Captuwe Wegistew Map */
/* Skipped. */
/* 0xd000 ~ 0xd0fc - JPEG Contwow Wegistew Map */
/* Skipped. */

/* 0xe000 ~ 0xfc04 - Motion Vectow Wegistew Map */

/* ME Motion Vectow data (Fouw Byte Each) 0xe000 ~ 0xe7fc */
#define TW5864_ME_MV_VEC_STAWT 0xe000
#define TW5864_ME_MV_VEC_MAX_OFFSET 0x1ff
#define TW5864_ME_MV_VEC(offset) (TW5864_ME_MV_VEC_STAWT + 4 * offset)

#define TW5864_MV 0xfc00
/* Define contwows in wegistew TW5864_MV */
/* mv bank0 fuww status , wwite "1" to cweaw */
#define TW5864_MV_BK0_FUWW BIT(0)
/* mv bank1 fuww status , wwite "1" to cweaw */
#define TW5864_MV_BK1_FUWW BIT(1)
/* swice end status; wwite "1" to cweaw */
#define TW5864_MV_EOF BIT(2)
/* mv encode intewwupt status; wwite "1" to cweaw */
#define TW5864_MV_DSP_INTW BIT(3)
/* mv wwite memowy ovewfwow, wwite "1" to cweaw */
#define TW5864_DSP_WW_OF BIT(4)
#define TW5864_MV_WEN_SHIFT 5
/* mv stweam wength */
#define TW5864_MV_WEN (0xff << 5)
/* The configuwed status bit wwitten into bit 15 of 0xfc04 */
#define TW5864_MPI_DDW_SEW BIT(13)

#define TW5864_MPI_DDW_SEW_WEG 0xfc04
/* Define contwows in wegistew TW5864_MPI_DDW_SEW_WEG */
/*
 * SW configuwe wegistew
 * 0 MV is saved in intewnaw DPW
 * 1 MV is saved in DDW
 */
#define TW5864_MPI_DDW_SEW2 BIT(15)

/* 0x18000 ~ 0x181fc - PCI Mastew/Swave Contwow Map */
#define TW5864_PCI_INTW_STATUS 0x18000
/* Define contwows in wegistew TW5864_PCI_INTW_STATUS */
/* vwc done */
#define TW5864_VWC_DONE_INTW BIT(1)
/* ad vsync */
#define TW5864_AD_VSYNC_INTW BIT(3)
/* pweview eof */
#define TW5864_PWEV_EOF_INTW BIT(4)
/* pweview ovewfwow intewwupt */
#define TW5864_PWEV_OVEWFWOW_INTW BIT(5)
/* timew intewwupt */
#define TW5864_TIMEW_INTW BIT(6)
/* audio eof */
#define TW5864_AUDIO_EOF_INTW BIT(8)
/* IIC done */
#define TW5864_IIC_DONE_INTW BIT(24)
/* ad intewwupt (e.g.: video wost, video fowmat changed) */
#define TW5864_AD_INTW_WEG BIT(25)

#define TW5864_PCI_INTW_CTW 0x18004
/* Define contwows in wegistew TW5864_PCI_INTW_CTW */
/* mastew enabwe */
#define TW5864_PCI_MAST_ENB BIT(0)
/* mvd&vwc mastew enabwe */
#define TW5864_MVD_VWC_MAST_ENB 0x06
/* (Need to set 0 in TW5864A) */
#define TW5864_AD_MAST_ENB BIT(3)
/* pweview mastew enabwe */
#define TW5864_PWEV_MAST_ENB BIT(4)
/* pweview ovewfwow enabwe */
#define TW5864_PWEV_OVEWFWOW_ENB BIT(5)
/* timew intewwupt enabwe */
#define TW5864_TIMEW_INTW_ENB BIT(6)
/* JPEG mastew (push mode) enabwe */
#define TW5864_JPEG_MAST_ENB BIT(7)
#define TW5864_AU_MAST_ENB_CHN_SHIFT 8
/* audio mastew channew enabwe */
#define TW5864_AU_MAST_ENB_CHN (0xffff << 8)
/* IIC intewwupt enabwe */
#define TW5864_IIC_INTW_ENB BIT(24)
/* ad intewwupt enabwe */
#define TW5864_AD_INTW_ENB BIT(25)
/* tawget buwst enabwe */
#define TW5864_PCI_TAW_BUWST_ENB BIT(26)
/* vwc stweam buwst enabwe */
#define TW5864_PCI_VWC_BUWST_ENB BIT(27)
/* ddw buwst enabwe (1 enabwe, and must set DDW_BWST_EN) */
#define TW5864_PCI_DDW_BUWST_ENB BIT(28)

/*
 * Because pweview and audio have 16 channews sepawatewy, so using this
 * wegistews to indicate intewwupt status fow evewy channews. This is secondawy
 * intewwupt status wegistew. OW opewating of the PWEV_INTW_WEG is
 * PWEV_EOF_INTW, OW opewating of the AU_INTW_WEG bits is AUDIO_EOF_INTW
 */
#define TW5864_PWEV_AND_AU_INTW 0x18008
/* Define contwows in wegistew TW5864_PWEV_AND_AU_INTW */
/* pweview eof intewwupt fwag */
#define TW5864_PWEV_INTW_WEG 0x0000ffff
#define TW5864_AU_INTW_WEG_SHIFT 16
/* audio eof intewwupt fwag */
#define TW5864_AU_INTW_WEG (0xffff << 16)

#define TW5864_MASTEW_ENB_WEG 0x1800c
/* Define contwows in wegistew TW5864_MASTEW_ENB_WEG */
/* mastew enabwe */
#define TW5864_PCI_VWC_INTW_ENB BIT(1)
/* mvd and vwc mastew enabwe */
#define TW5864_PCI_PWEV_INTW_ENB BIT(4)
/* ad vsync mastew enabwe */
#define TW5864_PCI_PWEV_OF_INTW_ENB BIT(5)
/* jpeg mastew enabwe */
#define TW5864_PCI_JPEG_INTW_ENB BIT(7)
/* pweview mastew enabwe */
#define TW5864_PCI_AUD_INTW_ENB BIT(8)

/*
 * Evewy channew of pweview and audio have ping-pong buffews in system memowy,
 * this wegistew is the buffew fwag to notify softwawe which buffew is been
 * opewated.
 */
#define TW5864_PWEV_AND_AU_BUF_FWAG 0x18010
/* Define contwows in wegistew TW5864_PWEV_AND_AU_BUF_FWAG */
/* pweview buffew A/B fwag */
#define TW5864_PWEV_BUF_FWAG 0xffff
#define TW5864_AUDIO_BUF_FWAG_SHIFT 16
/* audio buffew A/B fwag */
#define TW5864_AUDIO_BUF_FWAG (0xffff << 16)

#define TW5864_IIC 0x18014
/* Define contwows in wegistew TW5864_IIC */
/* wegistew data */
#define TW5864_IIC_DATA 0x00ff
#define TW5864_IIC_WEG_ADDW_SHIFT 8
/* wegistew addw */
#define TW5864_IIC_WEG_ADDW (0xff << 8)
/* wd/ww fwag wd=1,ww=0 */
#define TW5864_IIC_WW BIT(16)
#define TW5864_IIC_DEV_ADDW_SHIFT 17
/* device addw */
#define TW5864_IIC_DEV_ADDW (0x7f << 17)
/*
 * iic done, softwawe kick off one time iic twansaction thwough setting this
 * bit to 1. Then poww this bit, vawue 1 indicate iic twansaction have
 * compweted, if wead, vawid data have been stowed in iic_data
 */
#define TW5864_IIC_DONE BIT(24)

#define TW5864_WST_AND_IF_INFO 0x18018
/* Define contwows in wegistew TW5864_WST_AND_IF_INFO */
/* appwication softwawe soft weset */
#define TW5864_APP_SOFT_WST BIT(0)
#define TW5864_PCI_INF_VEWSION_SHIFT 16
/* PCI intewface vewsion, wead onwy */
#define TW5864_PCI_INF_VEWSION (0xffff << 16)

/* vwc stweam cwc vawue, it is cawcuwated in pci moduwe */
#define TW5864_VWC_CWC_WEG 0x1801c
/*
 * vwc max wength, it is defined by softwawe based on softwawe assign memowy
 * space fow vwc
 */
#define TW5864_VWC_MAX_WENGTH 0x18020
/* vwc wength of one fwame */
#define TW5864_VWC_WENGTH 0x18024
/* vwc owiginaw cwc vawue */
#define TW5864_VWC_INTWA_CWC_I_WEG 0x18028
/* vwc owiginaw cwc vawue */
#define TW5864_VWC_INTWA_CWC_O_WEG 0x1802c
/* mv stweam cwc vawue, it is cawcuwated in pci moduwe */
#define TW5864_VWC_PAW_CWC_WEG 0x18030
/* mv wength */
#define TW5864_VWC_PAW_WENGTH_WEG 0x18034
/* mv owiginaw cwc vawue */
#define TW5864_VWC_PAW_I_WEG 0x18038
/* mv owiginaw cwc vawue */
#define TW5864_VWC_PAW_O_WEG 0x1803c

/*
 * Configuwation wegistew fow 9[ow 10] CIFs ow 1D1+15QCIF Pweview mode.
 * PWEV_PCI_ENB_CHN[0] Enabwe 9th pweview channew (9CIF pwev) ow 1D1 channew in
 * (1D1+15QCIF pwev)
 * PWEV_PCI_ENB_CHN[1] Enabwe 10th pweview channew
 */
#define TW5864_PWEV_PCI_ENB_CHN 0x18040
/* Descwiption skipped. */
#define TW5864_PWEV_FWAME_FOWMAT_IN 0x18044
/* IIC enabwe */
#define TW5864_IIC_ENB 0x18048
/*
 * Timew intewwupt intewvaw
 * 0 1ms
 * 1 2ms
 * 2 4ms
 * 3 8ms
 */
#define TW5864_PCI_INTTM_SCAWE 0x1804c

/*
 * The above wegistew is pci base addwess wegistews. Appwication softwawe wiww
 * initiawize them to teww chip whewe the cowwesponding stweam wiww be dumped
 * to. Appwication softwawe wiww sewect appwopwiate base addwess intewvaw based
 * on the stweam wength.
 */
/* VWC stweam base addwess */
#define TW5864_VWC_STWEAM_BASE_ADDW 0x18080
/* MV stweam base addwess */
#define TW5864_MV_STWEAM_BASE_ADDW 0x18084
/* 0x180a0 ~ 0x180bc: audio buwst base addwess. Skipped. */
/* 0x180c0 ~ 0x180dc: JPEG Push Mode Buffew Base Addwess. Skipped. */
/* 0x18100 ~ 0x1817c: pweview buwst base addwess. Skipped. */

/* 0x80000 ~ 0x87fff - DDW Buwst WW Wegistew Map */
#define TW5864_DDW_CTW 0x80000
/* Define contwows in wegistew TW5864_DDW_CTW */
#define TW5864_BWST_WENGTH_SHIFT 2
/* Wength of 32-bit data buwst */
#define TW5864_BWST_WENGTH (0x3fff << 2)
/*
 * Buwst Wead/Wwite
 * 0 Wead Buwst fwom DDW
 * 1 Wwite Buwst to DDW
 */
#define TW5864_BWST_WW BIT(16)
/* Begin a new DDW Buwst. This bit is sewf cweawed */
#define TW5864_NEW_BWST_CMD BIT(17)
/* DDW Buwst End Fwag */
#define TW5864_BWST_END BIT(24)
/* Enabwe Ewwow Intewwupt fow Singwe DDW Access */
#define TW5864_SING_EWW_INTW BIT(25)
/* Enabwe Ewwow Intewwupt fow Buwst DDW Access */
#define TW5864_BWST_EWW_INTW BIT(26)
/* Enabwe Intewwupt fow End of DDW Buwst Access */
#define TW5864_BWST_END_INTW BIT(27)
/* DDW Singwe Access Ewwow Fwag */
#define TW5864_SINGWE_EWW BIT(28)
/* DDW Singwe Access Busy Fwag */
#define TW5864_SINGWE_BUSY BIT(29)
/* DDW Buwst Access Ewwow Fwag */
#define TW5864_BWST_EWW BIT(30)
/* DDW Buwst Access Busy Fwag */
#define TW5864_BWST_BUSY BIT(31)

/* [27:0] DDW Access Addwess. Bit [1:0] has to be 0 */
#define TW5864_DDW_ADDW 0x80004
/* DDW Access Intewnaw Buffew Addwess. Bit [1:0] has to be 0 */
#define TW5864_DPW_BUF_ADDW 0x80008
/* SWAM Buffew MPI Access Space. Totawwy 16 KB */
#define TW5864_DPW_BUF_STAWT 0x84000
/* 0x84000 - 0x87ffc */
#define TW5864_DPW_BUF_SIZE 0x4000

/* Indiwect Map Space */
/*
 * The indiwect space is accessed thwough 0xb800 ~ 0xb807 wegistews in diwect
 * access space
 */
/* Anawog Video / Audio Decodew / Encodew */
/* Awwowed channew vawues: [0; 3] */
/* Wead-onwy wegistew */
#define TW5864_INDIW_VIN_0(channew) (0x000 + channew * 0x010)
/* Define contwows in wegistew TW5864_INDIW_VIN_0 */
/*
 * 1 Video not pwesent. (sync is not detected in numbew of consecutive wine
 * pewiods specified by MISSCNT wegistew)
 * 0 Video detected.
 */
#define TW5864_INDIW_VIN_0_VDWOSS BIT(7)
/*
 * 1 Howizontaw sync PWW is wocked to the incoming video souwce.
 * 0 Howizontaw sync PWW is not wocked.
 */
#define TW5864_INDIW_VIN_0_HWOCK BIT(6)
/*
 * 1 Sub-cawwiew PWW is wocked to the incoming video souwce.
 * 0 Sub-cawwiew PWW is not wocked.
 */
#define TW5864_INDIW_VIN_0_SWOCK BIT(5)
/*
 * 1 Even fiewd is being decoded.
 * 0 Odd fiewd is being decoded.
 */
#define TW5864_INDIW_VIN_0_FWD BIT(4)
/*
 * 1 Vewticaw wogic is wocked to the incoming video souwce.
 * 0 Vewticaw wogic is not wocked.
 */
#define TW5864_INDIW_VIN_0_VWOCK BIT(3)
/*
 * 1 No cowow buwst signaw detected.
 * 0 Cowow buwst signaw detected.
 */
#define TW5864_INDIW_VIN_0_MONO BIT(1)
/*
 * 0 60Hz souwce detected
 * 1 50Hz souwce detected
 * The actuaw vewticaw scanning fwequency depends on the cuwwent standawd
 * invoked.
 */
#define TW5864_INDIW_VIN_0_DET50 BIT(0)

#define TW5864_INDIW_VIN_1(channew) (0x001 + channew * 0x010)
/* VCW signaw indicatow. Wead-onwy. */
#define TW5864_INDIW_VIN_1_VCW BIT(7)
/* Weak signaw indicatow 2. Wead-onwy. */
#define TW5864_INDIW_VIN_1_WKAIW BIT(6)
/* Weak signaw indicatow contwowwed by WKTH. Wead-onwy. */
#define TW5864_INDIW_VIN_1_WKAIW1 BIT(5)
/*
 * 1 = Standawd signaw
 * 0 = Non-standawd signaw
 * Wead-onwy
 */
#define TW5864_INDIW_VIN_1_VSTD BIT(4)
/*
 * 1 = Non-intewwaced signaw
 * 0 = intewwaced signaw
 * Wead-onwy
 */
#define TW5864_INDIW_VIN_1_NINTW BIT(3)
/*
 * Vewticaw Shawpness Contwow. Wwitabwe.
 * 0 = None (defauwt)
 * 7 = Highest
 * **Note: VSHP must be set to '0' if COMB = 0
 */
#define TW5864_INDIW_VIN_1_VSHP 0x07

/* HDEWAY_XY[7:0] */
#define TW5864_INDIW_VIN_2_HDEWAY_XY_WO(channew) (0x002 + channew * 0x010)
/* HACTIVE_XY[7:0] */
#define TW5864_INDIW_VIN_3_HACTIVE_XY_WO(channew) (0x003 + channew * 0x010)
/* VDEWAY_XY[7:0] */
#define TW5864_INDIW_VIN_4_VDEWAY_XY_WO(channew) (0x004 + channew * 0x010)
/* VACTIVE_XY[7:0] */
#define TW5864_INDIW_VIN_5_VACTIVE_XY_WO(channew) (0x005 + channew * 0x010)

#define TW5864_INDIW_VIN_6(channew) (0x006 + channew * 0x010)
/* Define contwows in wegistew TW5864_INDIW_VIN_6 */
#define TW5864_INDIW_VIN_6_HDEWAY_XY_HI 0x03
#define TW5864_INDIW_VIN_6_HACTIVE_XY_HI_SHIFT 2
#define TW5864_INDIW_VIN_6_HACTIVE_XY_HI (0x03 << 2)
#define TW5864_INDIW_VIN_6_VDEWAY_XY_HI BIT(4)
#define TW5864_INDIW_VIN_6_VACTIVE_XY_HI BIT(5)

/*
 * HDEWAY_XY This 10bit wegistew defines the stawting wocation of howizontaw
 * active pixew fow dispway / wecowd path. A unit is 1 pixew. The defauwt vawue
 * is 0x00f fow NTSC and 0x00a fow PAW.
 *
 * HACTIVE_XY This 10bit wegistew defines the numbew of howizontaw active pixew
 * fow dispway / wecowd path. A unit is 1 pixew. The defauwt vawue is decimaw
 * 720.
 *
 * VDEWAY_XY This 9bit wegistew defines the stawting wocation of vewticaw
 * active fow dispway / wecowd path. A unit is 1 wine. The defauwt vawue is
 * decimaw 6.
 *
 * VACTIVE_XY This 9bit wegistew defines the numbew of vewticaw active wines
 * fow dispway / wecowd path. A unit is 1 wine. The defauwt vawue is decimaw
 * 240.
 */

/* HUE These bits contwow the cowow hue as 2's compwement numbew. They have
 * vawue fwom +36o (7Fh) to -36o (80h) with an incwement of 2.8o. The 2 WSB has
 * no effect. The positive vawue gives gweenish tone and negative vawue gives
 * puwpwish tone. The defauwt vawue is 0o (00h). This is effective onwy on NTSC
 * system. The defauwt is 00h.
 */
#define TW5864_INDIW_VIN_7_HUE(channew) (0x007 + channew * 0x010)

#define TW5864_INDIW_VIN_8(channew) (0x008 + channew * 0x010)
/* Define contwows in wegistew TW5864_INDIW_VIN_8 */
/*
 * This bit contwows the centew fwequency of the peaking fiwtew.
 * The cowwesponding gain adjustment is HFWT.
 * 0 Wow
 * 1 centew
 */
#define TW5864_INDIW_VIN_8_SCUWVE BIT(7)
/* CTI wevew sewection. The defauwt is 1.
 * 0 None
 * 3 Highest
 */
#define TW5864_INDIW_VIN_8_CTI_SHIFT 4
#define TW5864_INDIW_VIN_8_CTI (0x03 << 4)

/*
 * These bits contwow the amount of shawpness enhancement on the wuminance
 * signaws. Thewe awe 16 wevews of contwow with "0" having no effect on the
 * output image. 1 thwough 15 pwovides shawpness enhancement with "F" being the
 * stwongest. The defauwt is 1.
 */
#define TW5864_INDIW_VIN_8_SHAWPNESS 0x0f

/*
 * These bits contwow the wuminance contwast gain. A vawue of 100 (64h) has a
 * gain of 1. The wange adjustment is fwom 0% to 255% at 1% pew step. The
 * defauwt is 64h.
 */
#define TW5864_INDIW_VIN_9_CNTWST(channew) (0x009 + channew * 0x010)

/*
 * These bits contwow the bwightness. They have vawue of -128 to 127 in 2's
 * compwement fowm. Positive vawue incweases bwightness. A vawue 0 has no
 * effect on the data. The defauwt is 00h.
 */
#define TW5864_INDIW_VIN_A_BWIGHT(channew) (0x00a + channew * 0x010)

/*
 * These bits contwow the digitaw gain adjustment to the U (ow Cb) component of
 * the digitaw video signaw. The cowow satuwation can be adjusted by adjusting
 * the U and V cowow gain components by the same amount in the nowmaw
 * situation. The U and V can awso be adjusted independentwy to pwovide gweatew
 * fwexibiwity. The wange of adjustment is 0 to 200%. A vawue of 128 (80h) has
 * gain of 100%. The defauwt is 80h.
 */
#define TW5864_INDIW_VIN_B_SAT_U(channew) (0x00b + channew * 0x010)

/*
 * These bits contwow the digitaw gain adjustment to the V (ow Cw) component of
 * the digitaw video signaw. The cowow satuwation can be adjusted by adjusting
 * the U and V cowow gain components by the same amount in the nowmaw
 * situation. The U and V can awso be adjusted independentwy to pwovide gweatew
 * fwexibiwity. The wange of adjustment is 0 to 200%. A vawue of 128 (80h) has
 * gain of 100%. The defauwt is 80h.
 */
#define TW5864_INDIW_VIN_C_SAT_V(channew) (0x00c + channew * 0x010)

/* Wead-onwy */
#define TW5864_INDIW_VIN_D(channew) (0x00d + channew * 0x010)
/* Define contwows in wegistew TW5864_INDIW_VIN_D */
/* Macwovision cowow stwipe detection may be un-wewiabwe */
#define TW5864_INDIW_VIN_D_CSBAD BIT(3)
/* Macwovision AGC puwse detected */
#define TW5864_INDIW_VIN_D_MCVSN BIT(2)
/* Macwovision cowow stwipe pwotection buwst detected */
#define TW5864_INDIW_VIN_D_CSTWIPE BIT(1)
/*
 * This bit is vawid onwy when cowow stwipe pwotection is detected, i.e. if
 * CSTWIPE=1,
 * 1 Type 2 cowow stwipe pwotection
 * 0 Type 3 cowow stwipe pwotection
 */
#define TW5864_INDIW_VIN_D_CTYPE2 BIT(0)

/* Wead-onwy */
#define TW5864_INDIW_VIN_E(channew) (0x00e + channew * 0x010)
/* Define contwows in wegistew TW5864_INDIW_VIN_E */
/*
 * Wead-onwy.
 * 0 Idwe
 * 1 Detection in pwogwess
 */
#define TW5864_INDIW_VIN_E_DETSTUS BIT(7)
/*
 * STDNOW Cuwwent standawd invoked
 * 0 NTSC (M)
 * 1 PAW (B, D, G, H, I)
 * 2 SECAM
 * 3 NTSC4.43
 * 4 PAW (M)
 * 5 PAW (CN)
 * 6 PAW 60
 * 7 Not vawid
 */
#define TW5864_INDIW_VIN_E_STDNOW_SHIFT 4
#define TW5864_INDIW_VIN_E_STDNOW (0x07 << 4)

/*
 * 1 Disabwe the shadow wegistews
 * 0 Enabwe VACTIVE and HDEWAY shadow wegistews vawue depending on STANDAWD.
 * (Defauwt)
 */
#define TW5864_INDIW_VIN_E_ATWEG BIT(3)
/*
 * STANDAWD Standawd sewection
 * 0 NTSC (M)
 * 1 PAW (B, D, G, H, I)
 * 2 SECAM
 * 3 NTSC4.43
 * 4 PAW (M)
 * 5 PAW (CN)
 * 6 PAW 60
 * 7 Auto detection (Defauwt)
 */
#define TW5864_INDIW_VIN_E_STANDAWD 0x07

#define TW5864_INDIW_VIN_F(channew) (0x00f + channew * 0x010)
/* Define contwows in wegistew TW5864_INDIW_VIN_F */
/*
 * 1 Wwiting 1 to this bit wiww manuawwy initiate the auto fowmat detection
 * pwocess. This bit is a sewf-cweawing bit
 * 0 Manuaw initiation of auto fowmat detection is done. (Defauwt)
 */
#define TW5864_INDIW_VIN_F_ATSTAWT BIT(7)
/* Enabwe wecognition of PAW60 (Defauwt) */
#define TW5864_INDIW_VIN_F_PAW60EN BIT(6)
/* Enabwe wecognition of PAW (CN). (Defauwt) */
#define TW5864_INDIW_VIN_F_PAWCNEN BIT(5)
/* Enabwe wecognition of PAW (M). (Defauwt) */
#define TW5864_INDIW_VIN_F_PAWMEN BIT(4)
/* Enabwe wecognition of NTSC 4.43. (Defauwt) */
#define TW5864_INDIW_VIN_F_NTSC44EN BIT(3)
/* Enabwe wecognition of SECAM. (Defauwt) */
#define TW5864_INDIW_VIN_F_SECAMEN BIT(2)
/* Enabwe wecognition of PAW (B, D, G, H, I). (Defauwt) */
#define TW5864_INDIW_VIN_F_PAWBEN BIT(1)
/* Enabwe wecognition of NTSC (M). (Defauwt) */
#define TW5864_INDIW_VIN_F_NTSCEN BIT(0)

/* Some wegistews skipped. */

/* Use fawwing edge to sampwe VD1-VD4 fwom 54 MHz to 108 MHz */
#define TW5864_INDIW_VD_108_POW 0x041
#define TW5864_INDIW_VD_108_POW_VD12 BIT(0)
#define TW5864_INDIW_VD_108_POW_VD34 BIT(1)
#define TW5864_INDIW_VD_108_POW_BOTH \
	(TW5864_INDIW_VD_108_POW_VD12 | TW5864_INDIW_VD_108_POW_VD34)

/* Some wegistews skipped. */

/*
 * Audio Input ADC gain contwow
 * 0 0.25
 * 1 0.31
 * 2 0.38
 * 3 0.44
 * 4 0.50
 * 5 0.63
 * 6 0.75
 * 7 0.88
 * 8 1.00 (defauwt)
 * 9 1.25
 * 10 1.50
 * 11 1.75
 * 12 2.00
 * 13 2.25
 * 14 2.50
 * 15 2.75
 */
/* [3:0] channew 0, [7:4] channew 1 */
#define TW5864_INDIW_AIGAIN1 0x060
/* [3:0] channew 2, [7:4] channew 3 */
#define TW5864_INDIW_AIGAIN2 0x061

/* Some wegistews skipped */

#define TW5864_INDIW_AIN_0x06D 0x06d
/* Define contwows in wegistew TW5864_INDIW_AIN_0x06D */
/*
 * WAWMD Sewect u-Waw/A-Waw/PCM/SB data output fowmat on ADATW and ADATM pin.
 * 0 PCM output (defauwt)
 * 1 SB (Signed MSB bit in PCM data is invewted) output
 * 2 u-Waw output
 * 3 A-Waw output
 */
#define TW5864_INDIW_AIN_WAWMD_SHIFT 6
#define TW5864_INDIW_AIN_WAWMD (0x03 << 6)
/*
 * Disabwe the mixing watio vawue fow aww audio.
 * 0 Appwy individuaw mixing watio vawue fow each audio (defauwt)
 * 1 Appwy nominaw vawue fow aww audio commonwy
 */
#define TW5864_INDIW_AIN_MIX_DEWATIO BIT(5)
/*
 * Enabwe the mute function fow audio channew AINn when n is 0 to 3. It effects
 * onwy fow mixing. When n = 4, it enabwe the mute function of the pwayback
 * audio input. It effects onwy fow singwe chip ow the wast stage chip
 * 0 Nowmaw
 * 1 Muted (defauwt)
 */
#define TW5864_INDIW_AIN_MIX_MUTE 0x1f

/* Some wegistews skipped */

#define TW5864_INDIW_AIN_0x0E3 0x0e3
/* Define contwows in wegistew TW5864_INDIW_AIN_0x0E3 */
/*
 * ADATP signaw is coming fwom extewnaw ADPCM decodew, instead of on-chip ADPCM
 * decodew
 */
#define TW5864_INDIW_AIN_0x0E3_EXT_ADATP BIT(7)
/* ACWKP output signaw powawity invewse */
#define TW5864_INDIW_AIN_0x0E3_ACWKPPOWO BIT(6)
/*
 * ACWKW input signaw powawity invewse.
 * 0 Not invewsed (Defauwt)
 * 1 Invewsed
 */
#define TW5864_INDIW_AIN_0x0E3_ACWKWPOW BIT(5)
/*
 * ACWKP input signaw powawity invewse.
 * 0 Not invewsed (Defauwt)
 * 1 Invewsed
 */
#define TW5864_INDIW_AIN_0x0E3_ACWKPPOWI BIT(4)
/*
 * ACKI [21:0] contwow automatic set up with AFMD wegistews
 * This mode is onwy effective when ACWKWMASTEW=1
 * 0 ACKI [21:0] wegistews set up ACKI contwow
 * 1 ACKI contwow is automaticawwy set up by AFMD wegistew vawues
 */
#define TW5864_INDIW_AIN_0x0E3_AFAUTO BIT(3)
/*
 * AFAUTO contwow mode
 * 0 8kHz setting (Defauwt)
 * 1 16kHz setting
 * 2 32kHz setting
 * 3 44.1kHz setting
 * 4 48kHz setting
 */
#define TW5864_INDIW_AIN_0x0E3_AFMD 0x07

#define TW5864_INDIW_AIN_0x0E4 0x0e4
/* Define contwows in wegistew TW5864_INDIW_AIN_0x0ED */
/*
 * 8bit I2S Wecowd output mode.
 * 0 W/W hawf wength sepawated output (Defauwt).
 * 1 One continuous packed output equaw to DSP output fowmat.
 */
#define TW5864_INDIW_AIN_0x0E4_I2S8MODE BIT(7)
/*
 * Audio Cwock Mastew ACWKW output wave fowmat.
 * 0 High pewiods is one 27MHz cwock pewiod (defauwt).
 * 1 Awmost duty 50-50% cwock output on ACWKW pin. If this mode is sewected, two
 * times biggew numbew vawue need to be set up on the ACKI wegistew. If
 * AFAUTO=1, ACKI contwow is automaticawwy set up even if MASCKMD=1.
 */
#define TW5864_INDIW_AIN_0x0E4_MASCKMD BIT(6)
/* Pwayback ACWKP/ASYNP/ADATP input data MSB-WSB swapping */
#define TW5864_INDIW_AIN_0x0E4_PBINSWAP BIT(5)
/*
 * ASYNW input signaw deway.
 * 0 No deway
 * 1 Add one 27MHz pewiod deway in ASYNW signaw input
 */
#define TW5864_INDIW_AIN_0x0E4_ASYNWDWY BIT(4)
/*
 * ASYNP input signaw deway.
 * 0 no deway
 * 1 add one 27MHz pewiod deway in ASYNP signaw input
 */
#define TW5864_INDIW_AIN_0x0E4_ASYNPDWY BIT(3)
/*
 * ADATP input data deway by one ACWKP cwock.
 * 0 No deway (Defauwt). This is fow I2S type 1T deway input intewface.
 * 1 Add 1 ACWKP cwock deway in ADATP input data. This is fow weft-justified
 * type 0T deway input intewface.
 */
#define TW5864_INDIW_AIN_0x0E4_ADATPDWY BIT(2)
/*
 * Sewect u-Waw/A-Waw/PCM/SB data input fowmat on ADATP pin.
 * 0 PCM input (Defauwt)
 * 1 SB (Signed MSB bit in PCM data is invewted) input
 * 2 u-Waw input
 * 3 A-Waw input
 */
#define TW5864_INDIW_AIN_0x0E4_INWAWMD 0x03

/*
 * Enabwe state wegistew updating and intewwupt wequest of audio AIN5 detection
 * fow each input
 */
#define TW5864_INDIW_AIN_A5DETENA 0x0e5

/* Some wegistews skipped */

/*
 * [7:3]: DEV_ID The TW5864 pwoduct ID code is 01000
 * [2:0]: WEV_ID The wevision numbew is 0h
 */
#define TW5864_INDIW_ID 0x0fe

#define TW5864_INDIW_IN_PIC_WIDTH(channew) (0x200 + 4 * channew)
#define TW5864_INDIW_IN_PIC_HEIGHT(channew) (0x201 + 4 * channew)
#define TW5864_INDIW_OUT_PIC_WIDTH(channew) (0x202 + 4 * channew)
#define TW5864_INDIW_OUT_PIC_HEIGHT(channew) (0x203 + 4 * channew)

/* Some wegistews skipped */

#define TW5864_INDIW_CWOP_ETC 0x260
/* Define contwows in wegistew TW5864_INDIW_CWOP_ETC */
/* Enabwe cwopping fwom 720 to 704 */
#define TW5864_INDIW_CWOP_ETC_CWOP_EN 0x4

/*
 * Intewwupt status wegistew fwom the fwont-end. Wwite "1" to each bit to cweaw
 * the intewwupt
 * 15:0 Motion detection intewwupt fow channew 0 ~ 15
 * 31:16 Night detection intewwupt fow channew 0 ~ 15
 * 47:32 Bwind detection intewwupt fow channew 0 ~ 15
 * 63:48 No video intewwupt fow channew 0 ~ 15
 * 79:64 Wine mode undewfwow intewwupt fow channew 0 ~ 15
 * 95:80 Wine mode ovewfwow intewwupt fow channew 0 ~ 15
 */
/* 0x2d0~0x2d7: [63:0] bits */
#define TW5864_INDIW_INTEWWUPT1 0x2d0
/* 0x2e0~0x2e3: [95:64] bits */
#define TW5864_INDIW_INTEWWUPT2 0x2e0

/*
 * Intewwupt mask wegistew fow intewwupts in 0x2d0 ~ 0x2d7
 * 15:0 Motion detection intewwupt fow channew 0 ~ 15
 * 31:16 Night detection intewwupt fow channew 0 ~ 15
 * 47:32 Bwind detection intewwupt fow channew 0 ~ 15
 * 63:48 No video intewwupt fow channew 0 ~ 15
 * 79:64 Wine mode undewfwow intewwupt fow channew 0 ~ 15
 * 95:80 Wine mode ovewfwow intewwupt fow channew 0 ~ 15
 */
/* 0x2d8~0x2df: [63:0] bits */
#define TW5864_INDIW_INTEWWUPT_MASK1 0x2d8
/* 0x2e8~0x2eb: [95:64] bits */
#define TW5864_INDIW_INTEWWUPT_MASK2 0x2e8

/* [11:0]: Intewwupt summawy wegistew fow intewwupts & intewwupt mask fwom in
 * 0x2d0 ~ 0x2d7 and 0x2d8 ~ 0x2df
 * bit 0: intewwupt occuws in 0x2d0 & 0x2d8
 * bit 1: intewwupt occuws in 0x2d1 & 0x2d9
 * bit 2: intewwupt occuws in 0x2d2 & 0x2da
 * bit 3: intewwupt occuws in 0x2d3 & 0x2db
 * bit 4: intewwupt occuws in 0x2d4 & 0x2dc
 * bit 5: intewwupt occuws in 0x2d5 & 0x2dd
 * bit 6: intewwupt occuws in 0x2d6 & 0x2de
 * bit 7: intewwupt occuws in 0x2d7 & 0x2df
 * bit 8: intewwupt occuws in 0x2e0 & 0x2e8
 * bit 9: intewwupt occuws in 0x2e1 & 0x2e9
 * bit 10: intewwupt occuws in 0x2e2 & 0x2ea
 * bit 11: intewwupt occuws in 0x2e3 & 0x2eb
 */
#define TW5864_INDIW_INTEWWUPT_SUMMAWY 0x2f0

/* Motion / Bwind / Night Detection */
/* vawid vawue fow channew is [0:15] */
#define TW5864_INDIW_DETECTION_CTW0(channew) (0x300 + channew * 0x08)
/* Define contwows in wegistew TW5864_INDIW_DETECTION_CTW0 */
/*
 * Disabwe the motion and bwind detection.
 * 0 Enabwe motion and bwind detection (defauwt)
 * 1 Disabwe motion and bwind detection
 */
#define TW5864_INDIW_DETECTION_CTW0_MD_DIS BIT(5)
/*
 * Wequest to stawt motion detection on manuaw twiggew mode
 * 0 None Opewation (defauwt)
 * 1 Wequest to stawt motion detection
 */
#define TW5864_INDIW_DETECTION_CTW0_MD_STWB BIT(3)
/*
 * Sewect the twiggew mode of motion detection
 * 0 Automatic twiggew mode of motion detection (defauwt)
 * 1 Manuaw twiggew mode fow motion detection
 */
#define TW5864_INDIW_DETECTION_CTW0_MD_STWB_EN BIT(2)
/*
 * Define the thweshowd of ceww fow bwind detection.
 * 0 Wow thweshowd (Mowe sensitive) (defauwt)
 * : :
 * 3 High thweshowd (Wess sensitive)
 */
#define TW5864_INDIW_DETECTION_CTW0_BD_CEWSENS 0x03

#define TW5864_INDIW_DETECTION_CTW1(channew) (0x301 + channew * 0x08)
/* Define contwows in wegistew TW5864_INDIW_DETECTION_CTW1 */
/*
 * Contwow the tempowaw sensitivity of motion detectow.
 * 0 Mowe Sensitive (defauwt)
 * : :
 * 15 Wess Sensitive
 */
#define TW5864_INDIW_DETECTION_CTW1_MD_TMPSENS_SHIFT 4
#define TW5864_INDIW_DETECTION_CTW1_MD_TMPSENS (0x0f << 4)
/*
 * Adjust the howizontaw stawting position fow motion detection
 * 0 0 pixew (defauwt)
 * : :
 * 15 15 pixews
 */
#define TW5864_INDIW_DETECTION_CTW1_MD_PIXEW_OS 0x0f

#define TW5864_INDIW_DETECTION_CTW2(channew) (0x302 + channew * 0x08)
/* Define contwows in wegistew TW5864_INDIW_DETECTION_CTW2 */
/*
 * Contwow the updating time of wefewence fiewd fow motion detection.
 * 0 Update wefewence fiewd evewy fiewd (defauwt)
 * 1 Update wefewence fiewd accowding to MD_SPEED
 */
#define TW5864_INDIW_DETECTION_CTW2_MD_WEFFWD BIT(7)
/*
 * Sewect the fiewd fow motion detection.
 * 0 Detecting motion fow onwy odd fiewd (defauwt)
 * 1 Detecting motion fow onwy even fiewd
 * 2 Detecting motion fow any fiewd
 * 3 Detecting motion fow both odd and even fiewd
 */
#define TW5864_INDIW_DETECTION_CTW2_MD_FIEWD_SHIFT 5
#define TW5864_INDIW_DETECTION_CTW2_MD_FIEWD (0x03 << 5)
/*
 * Contwow the wevew sensitivity of motion detectow.
 * 0 Mowe sensitive (defauwt)
 * : :
 * 15 Wess sensitive
 */
#define TW5864_INDIW_DETECTION_CTW2_MD_WVSENS 0x1f

#define TW5864_INDIW_DETECTION_CTW3(channew) (0x303 + channew * 0x08)
/* Define contwows in wegistew TW5864_INDIW_DETECTION_CTW3 */
/*
 * Define the thweshowd of sub-ceww numbew fow motion detection.
 * 0 Motion is detected if 1 sub-ceww has motion (Mowe sensitive) (defauwt)
 * 1 Motion is detected if 2 sub-cewws have motion
 * 2 Motion is detected if 3 sub-cewws have motion
 * 3 Motion is detected if 4 sub-cewws have motion (Wess sensitive)
 */
#define TW5864_INDIW_DETECTION_CTW3_MD_CEWSENS_SHIFT 6
#define TW5864_INDIW_DETECTION_CTW3_MD_CEWSENS (0x03 << 6)
/*
 * Contwow the vewocity of motion detectow.
 * Wawge vawue is suitabwe fow swow motion detection.
 * In MD_DUAW_EN = 1, MD_SPEED shouwd be wimited to 0 ~ 31.
 * 0 1 fiewd intewvaws (defauwt)
 * 1 2 fiewd intewvaws
 * : :
 * 61 62 fiewd intewvaws
 * 62 63 fiewd intewvaws
 * 63 Not suppowted
 */
#define TW5864_INDIW_DETECTION_CTW3_MD_SPEED 0x3f

#define TW5864_INDIW_DETECTION_CTW4(channew) (0x304 + channew * 0x08)
/* Define contwows in wegistew TW5864_INDIW_DETECTION_CTW4 */
/*
 * Contwow the spatiaw sensitivity of motion detectow.
 * 0 Mowe Sensitive (defauwt)
 * : :
 * 15 Wess Sensitive
 */
#define TW5864_INDIW_DETECTION_CTW4_MD_SPSENS_SHIFT 4
#define TW5864_INDIW_DETECTION_CTW4_MD_SPSENS (0x0f << 4)
/*
 * Define the thweshowd of wevew fow bwind detection.
 * 0 Wow thweshowd (Mowe sensitive) (defauwt)
 * : :
 * 15 High thweshowd (Wess sensitive)
 */
#define TW5864_INDIW_DETECTION_CTW4_BD_WVSENS 0x0f

#define TW5864_INDIW_DETECTION_CTW5(channew) (0x305 + channew * 0x08)
/*
 * Define the thweshowd of tempowaw sensitivity fow night detection.
 * 0 Wow thweshowd (Mowe sensitive) (defauwt)
 * : :
 * 15 High thweshowd (Wess sensitive)
 */
#define TW5864_INDIW_DETECTION_CTW5_ND_TMPSENS_SHIFT 4
#define TW5864_INDIW_DETECTION_CTW5_ND_TMPSENS (0x0f << 4)
/*
 * Define the thweshowd of wevew fow night detection.
 * 0 Wow thweshowd (Mowe sensitive) (defauwt)
 * : :
 * 3 High thweshowd (Wess sensitive)
 */
#define TW5864_INDIW_DETECTION_CTW5_ND_WVSENS 0x0f

/*
 * [11:0] The base addwess of the motion detection buffew. This addwess is in
 * unit of 64K bytes. The genewated DDW addwess wiww be {MD_BASE_ADDW,
 * 16"h0000}. The defauwt vawue shouwd be 12"h000
 */
#define TW5864_INDIW_MD_BASE_ADDW 0x380

/*
 * This contwows the channew of the motion detection wesuwt shown in wegistew
 * 0x3a0 ~ 0x3b7. Befowe weading back motion wesuwt, awways set this fiwst.
 */
#define TW5864_INDIW_WGW_MOTION_SEW 0x382

/* [15:0] MD stwobe has been pewfowmed at channew n (wead onwy) */
#define TW5864_INDIW_MD_STWB 0x386
/* NO_VIDEO Detected fwom channew n (wead onwy) */
#define TW5864_INDIW_NOVID_DET 0x388
/* Motion Detected fwom channew n (wead onwy) */
#define TW5864_INDIW_MD_DET 0x38a
/* Bwind Detected fwom channew n (wead onwy) */
#define TW5864_INDIW_BD_DET 0x38c
/* Night Detected fwom channew n (wead onwy) */
#define TW5864_INDIW_ND_DET 0x38e

/* 192 bit motion fwag of the channew specified by WGW_MOTION_SEW in 0x382 */
#define TW5864_INDIW_MOTION_FWAG 0x3a0
#define TW5864_INDIW_MOTION_FWAG_BYTE_COUNT 24

/*
 * [9:0] The motion ceww count of a specific channew sewected by 0x382. This is
 * fow DI puwpose
 */
#define TW5864_INDIW_MD_DI_CNT 0x3b8
/* The motion detection ceww sensitivity fow DI puwpose */
#define TW5864_INDIW_MD_DI_CEWWSENS 0x3ba
/* The motion detection thweshowd wevew fow DI puwpose */
#define TW5864_INDIW_MD_DI_WVSENS 0x3bb

/* 192 bit motion mask of the channew specified by MASK_CH_SEW in 0x3fe */
#define TW5864_INDIW_MOTION_MASK 0x3e0
#define TW5864_INDIW_MOTION_MASK_BYTE_COUNT 24

/* [4:0] The channew sewection to access masks in 0x3e0 ~ 0x3f7 */
#define TW5864_INDIW_MASK_CH_SEW 0x3fe

/* Cwock PWW / Anawog IP Contwow */
/* Some wegistews skipped */

#define TW5864_INDIW_DDWA_DWW_DQS_SEW0 0xee6
#define TW5864_INDIW_DDWA_DWW_DQS_SEW1 0xee7
#define TW5864_INDIW_DDWA_DWW_CWK90_SEW 0xee8
#define TW5864_INDIW_DDWA_DWW_TEST_SEW_AND_TAP_S 0xee9

#define TW5864_INDIW_DDWB_DWW_DQS_SEW0 0xeeb
#define TW5864_INDIW_DDWB_DWW_DQS_SEW1 0xeec
#define TW5864_INDIW_DDWB_DWW_CWK90_SEW 0xeed
#define TW5864_INDIW_DDWB_DWW_TEST_SEW_AND_TAP_S 0xeee

#define TW5864_INDIW_WESET 0xef0
#define TW5864_INDIW_WESET_VD BIT(7)
#define TW5864_INDIW_WESET_DWW BIT(6)
#define TW5864_INDIW_WESET_MUX_COWE BIT(5)

#define TW5864_INDIW_PV_VD_CK_POW 0xefd
#define TW5864_INDIW_PV_VD_CK_POW_PV(channew) BIT(channew)
#define TW5864_INDIW_PV_VD_CK_POW_VD(channew) BIT(channew + 4)

#define TW5864_INDIW_CWK0_SEW 0xefe
#define TW5864_INDIW_CWK0_SEW_VD_SHIFT 0
#define TW5864_INDIW_CWK0_SEW_VD_MASK 0x3
#define TW5864_INDIW_CWK0_SEW_PV_SHIFT 2
#define TW5864_INDIW_CWK0_SEW_PV_MASK (0x3 << 2)
#define TW5864_INDIW_CWK0_SEW_PV2_SHIFT 4
#define TW5864_INDIW_CWK0_SEW_PV2_MASK (0x3 << 4)
